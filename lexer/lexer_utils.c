/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 03:34:11 by adhaka            #+#    #+#             */
/*   Updated: 2023/12/01 06:09:34 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_checker(char *tmp, int i)
{
	while (tmp[i])
	{
		if (tmp[i] == '|')
		{
			if (tmp[i + 1] == '|' || (i == 0))
				return (-1);
			i++;
			while ((tmp[i] >= 9 && tmp[i] <= 13) || tmp[i] == 32)
				i++;
			if (!tmp[i])
				return (-1);
		}
		i++;
	}
	return (0);
}

void	fix_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		if (ft_strlen(tokens->cmd) == 0)
		{
			if (tokens->prev)
				tokens->prev->next = tokens->next;
			if (tokens->next)
				tokens->next->prev = tokens->prev;
			if (tokens->cmd)
				free(tokens->cmd);
			free(tokens);
		}
		tokens = next;
	}
}

int	lexer_redirects(int i, char *input)
{
	i++;
	if (input[i] == '<' || input[i] == '>')
		i++;
	if (input[i] == '<')
		i++;
	while (input[i] == ' ' && input[i] != '\0')
		i++;
	while (input[i] != ' ' && input[i] != '\0' && input[i] != '|')
		i++;
	return (i);
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
		if (cur_token->table != NULL)
		{
			if (cur_token->table->cmd_name != NULL)
				free(cur_token->table->cmd_name);
			if (cur_token->table->input_file != NULL)
				free(cur_token->table->input_file);
			if (cur_token->table->output_file != NULL)
				free(cur_token->table->output_file);
			free(cur_token->table);
		}
		free(cur_token);
		cur_token = next_token;
	}
	*token_list = NULL;
}
