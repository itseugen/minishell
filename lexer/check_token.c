/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:43:15 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/30 15:03:24 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief scans the lexer and assigns IDs
/// @param token_list 
void	assign_id(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current != NULL)
	{
		if (current->cmd[0] == '|')
			current->operation = PIPE;
		else if (current->cmd[0] == '<' && current->cmd[1] == '<')
			current->operation = HERE_DOC;
		else if (current->cmd[0] == '<' || current->cmd[0] == '>')
			current->operation = REDIRECT;
		// else if (current->cmd[0] == ';')
		// 	current->operation = SEMICOLON;
		else
			current->operation = CMD;
		current = current->next;
	}
}

bool	is_redirect(char *cmd)
{
	if (ft_strncmp(cmd, "<", 2) == 0)
		return (true);
	if (ft_strncmp(cmd, ">", 2) == 0)
		return (true);
	if (ft_strncmp(cmd, ">>", 3) == 0)
		return (true);
	return (false);
}
