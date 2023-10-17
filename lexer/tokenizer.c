/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:29:17 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/17 17:01:08 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_new(t_token **token_list);

t_token	*get_tokens(char *input)
{
	char	**split;
	int		i;
	t_token	*token_list;

	i = 0;
	token_list = NULL;
	split == ft_split_minishell(input, ' ');
	if (split == NULL)
		return (NULL);
	while (split[i] != NULL)
	{
		token_list = add_new(&token_list);
		i++;
	}
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
		*token_list = new_token;
	}
	else
	{
		last_token = *token_list;
		while (last_token->next != NULL)
			last_token = last_token->next;
		new_token->next = NULL;
		last_token->next = new_token;
	}
	return (0);
}

void	free_tokens(t_token **token_list)
{
	t_token	*free_me;

	while (token_list != NULL)
	{
		free_me = *token_list;
		*token_list = *token_list->next;
		free(free_me);
	}
}

// bool	is_file(char *str)
// {
// 	if (access(str, R_OK) == 0 || access(str, W_OK) == 0)
// 		return (true);
// 	return (false);
// }
