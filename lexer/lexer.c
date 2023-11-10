/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:30:19 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/10 01:46:03 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_new(t_token **token_list);
static char	*get_tok_str(int *old_i, char *input);
static int	skip_quotes(char const *s, int i);

//* The idea behind it is, to just split the string using my
//* minishell split. For execve we can then just pass the split
//* to the execve, same for the builtins (that have to be reworked slightly)
//* (echo has to split the string itself to print the spaces correctly)
//* For example cd takes a char **, checks if char **[2] == NULL
//* Fails if it isnt otherwise just executes as usual with
//* char **[1] (char **[0] should be "cd")

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
	// assign_id(&token_list);
	return (token_list);
}

static char	*get_tok_str(int *old_i, char *input)
{
	int	start;
	int	i;

	start = *old_i;
	i = *old_i;
	if (input[i] == '|')
		return ((*old_i)++, ft_strdup("|"));
	if (input[i] == ';')
		return ((*old_i)++, ft_strdup(";"));
	if (input[i] == '<' || input[i] == '>')
	{
		i++;
		if (input[i] == '<' || input[i] == '>')
			i++;
		while (input[i] == ' ' && input[i] != '\0')
			i++;
		while (input[i] != ' ' && input[i] != '\0')
			i++;
	}
	else
	{
		while (input[i] == ' ' && input[i] != '\0')
			i++;
		start = i;
		while (input[i] != '\0' && input[i] != '|' && input[i] != ';'
			&& input[i] != '<' && input[i] != '>')
		{
			i = skip_quotes(input, i);
			if (i == -1)
				return (ft_fprintf(2, "Unclosed quotes: aborting\n"), NULL);
			i++;
		}
	}
	*old_i = i;
	return (ft_substr(input, start, i - start));
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

void	free_tokens(t_token **token_list)
{
	t_token	*cur_token;
	t_token	*next_token;

	if (*token_list == NULL)
		return ;
	cur_token = *token_list;
	while (cur_token != NULL)
	{
		next_token = cur_token->next;
		if (cur_token->cmd != NULL)
			free(cur_token->cmd);
		free(cur_token);
		cur_token = next_token;
	}
	*token_list = NULL;
}
