/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:30:19 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/05 14:00:18 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_new(t_token **token_list);
static char	*get_tok_str(int *old_i, char *input);
static int	skip_quotes(char const *s, int i);

t_token	*tokenizer(char *input)
{
	t_token	*token_list;
	int		i;

	i = 0;
	token_list = NULL;
	while (input[i] != '\0')
	{
		if (add_new(&token_list) == 1)
			return (free_tokens(&token_list), NULL);
		token_list->cmd = get_tok_str(&i, input);
		if (token_list->cmd == NULL)
			return (free_tokens(&token_list), NULL);
	}
	return (token_list);
}

static char	*get_tok_str(int *old_i, char *input)
{
	int	start;
	int	i;

	start = *old_i;
	i = *old_i;
	if (input[i] == '|')
		return (*old_i++, ft_strdup("|"));
	if (input[i] == '<')
	{
		if (input[i + i] == '<')
			return (*old_i += 2, ft_strdup("<<"));
		return (*old_i++, ft_strdup("<"));
	}
	if (input[i] == '>')
	{
		if (input[i + i] == '>')
			return (*old_i += 2, ft_strdup(">>"));
		return (*old_i++, ft_strdup(">"));
	}
	while (input[i] != '\0' && input[i] != '|'
		&& input[i] != '<' && input[i] != '>')
	{
		i = skip_quotes(input, i);
		if (i == -1)
			return (NULL);
		i++;
	}
	*old_i = i;
	return (ft_substr(input, start, i - start - 1));
}

static int	skip_quotes(char const *s, int i)
{
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
	while (token_list != NULL)
	{
		next_token = cur_token->next;
		free(cur_token);
		cur_token = next_token;
	}
	*token_list = NULL;
}
