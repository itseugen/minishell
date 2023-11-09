/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:43:15 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/09 17:04:33 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/// @brief Returns true if the cmd is a builtin
/// @param cmd the command to check
/// @return true if it is a builtin, otherwise false
bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd ", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "echo ", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd ", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "export ", 7) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset ", 6) == 0)
		return (true);
	if (ft_strncmp(cmd, "env ", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit ", 5) == 0)
		return (true);
	return (false);
}
