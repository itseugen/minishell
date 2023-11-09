/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:02:45 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/09 16:28:39 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Takes the token list and expands all cmds
/// @param envp 
/// @param tokens the token list
/// @return 1 if the expander fails (malloc) otherwise 0
int	expand_tokens(char **envp, t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		current->cmd = expander(current->cmd, envp);
		if (current->cmd == NULL)
			return (1);
		current = current->next;
	}
	return (0);
}

void	t_print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		printf("Command: %s. ID: %d\n", tokens->cmd, tokens->operation);
		current = current->next;
	}
}
