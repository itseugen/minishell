/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:30:19 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/27 13:55:08 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_new(t_token **token_list);
static char	*get_tok_str(int *old_i, char *input);
static int	skip_quotes(char const *s, int i);
static int	lexer_normal_string(int i, char *input, int *start);

/// @brief Splits the input into tokens
/// @param input the input to split
/// @throws Fails on unclosed quotes and malloc fails
/// @return a list of tokens or NULL in case of fail
t_token	*tokenizer(char *input)
{
	t_token	*token_list;
	t_token	*current;
	int		i;

	i = 0;
	token_list = NULL;
	while (input[i] != '\0')
	{
		if (add_new(&token_list) == 1)
			return (free_tokens(&token_list), NULL);
		current = token_list;
		while (current->next != NULL)
			current = current->next;
		current->cmd = get_tok_str(&i, input);
		if (current->cmd == NULL)
			return (free_tokens(&token_list), NULL);
		current = current->next;
	}
	assign_id(token_list);
	return (token_list);
}

static char	*get_tok_str(int *old_i, char *input)
{
	int	start;
	int	i;

	start = *old_i;
	i = *old_i;
	if (input[i] == '|')
	{
		if (pipe_checker(input, i) == -1)
			return (NULL);
		return ((*old_i)++, ft_strdup("|"));
	}
	if (input[i] == ';')
		return ((*old_i)++, ft_strdup(";"));
	if ((input[i] == '<' && input[i + 1] == '>')
		|| (input[i] == '>' && input[i + 1] == '<'))
		return (NULL);
	if (input[i] == '<' || input[i] == '>')
		i = lexer_redirects(i, input);
	else
		i = lexer_normal_string(i, input, &start);
	if (i == -1)
		return (ft_fprintf(2, "Unclosed quotes: aborting\n"), NULL);
	*old_i = i;
	return (ft_substr(input, start, i - start));
}

static int	lexer_normal_string(int i, char *input, int *start)
{
	while (input[i] == ' ' && input[i] != '\0')
		i++;
	*(start) = i;
	while (input[i] != '\0' && input[i] != '|' && input[i] != ';'
		&& input[i] != '<' && input[i] != '>')
	{
		i = skip_quotes(input, i);
		if (i == -1)
			return (-1);
		i++;
	}
	return (i);
}

static int	skip_quotes(char const *s, int i)
{
	if (s[i] != '"' && s[i] != '\'')
		return (i);
	if (s[i] == '"')
	{
		i++;
		while (s[i] != '"' && s[i] != '\0')
			i++;
	}
	else
	{
		i++;
		while (s[i] != '\'' && s[i] != '\0')
			i++;
	}
	if (s[i] == '\0')
		return (-1);
	return (i);
}

static int	add_new(t_token **token_list)
{
	t_token	*new_token;
	t_token	*last_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		return (1);
	if (*token_list == NULL)
	{
		new_token->next = NULL;
		new_token->prev = NULL;
		*token_list = new_token;
	}
	else
	{
		last_token = *token_list;
		while (last_token->next != NULL)
			last_token = last_token->next;
		new_token->next = NULL;
		new_token->prev = last_token;
		last_token->next = new_token;
	}
	return (0);
}
