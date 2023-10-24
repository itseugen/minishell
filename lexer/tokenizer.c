/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:29:17 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/24 17:52:39 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_new(t_token **token_list);
static int	assign_tokens(t_token **token_list, char **split);

t_token	*get_tokens(char **split)
{
	int		i;
	t_token	*token_list;

	i = 0;
	token_list = NULL;
	while (split[i] != NULL)
	{
		if (add_new(&token_list) == 1)
			return (free_tokens(&token_list), NULL);
		i++;
	}
	assign_tokens(&token_list, split);
	return (token_list);
}

static int	assign_tokens(t_token **token_list, char **split)
{
	t_token	*current;
	int		i;

	current = *token_list;
	i = 0;
	while (split[i] != NULL)
	{
		current->cmd = split[i];
		if (is_builtin(current->cmd) == true)
			current->operation = BUILTIN;
		else if (ft_strncmp(current->cmd, "|", 2) == 0)
			current->operation = PIPE;
		else if (is_redirect(current->cmd) == true)
			current->operation = REDIRECT;
		else if (current->cmd[0] == '-')
			current->operation = ARGUMENT;
		else if (current->prev != NULL && current->prev->operation == REDIRECT)
			current->operation = FD;
		else if (ft_strncmp(current->cmd, "<<", 3) == 0)
			current->operation = HERE_DOC;
		else if (current->prev != NULL && current->prev->operation == HERE_DOC)
			current->operation = LIMITER;
		else
			current->operation = CMD;
		current = current->next;
		i++;
	}
	return (0);
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
