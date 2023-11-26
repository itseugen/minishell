/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 03:34:11 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/26 04:51:36 by adhaka           ###   ########.fr       */
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
	while (tokens)
	{
		if (ft_strlen(tokens->cmd) == 0)
		{
			tokens->prev->next = tokens->next;
			tokens->next->prev = tokens->prev;
			if (tokens->cmd)
				free(tokens->cmd);
			free(tokens);
		}
		tokens = tokens->next;
	}
}
