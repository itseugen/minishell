/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:17:58 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/09 16:55:40 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Checks if the str is a builtin function and executes
/// @param str 
/// @return false if it isnt, true if it is
// bool	is_builtin(char *str)
// {
// 	if (str == NULL)
// 		return (false);
// 	if (ft_strncmp(str, "cd", 3) == 0)
// 		return (true);
// 	// else if (ft_strncmp(str, "echo", 5) == 0)
// 	// 	return (true);
// 	else if (ft_strncmp(str, "pwd", 4) == 0)
// 		return (true);
// 	// else if (ft_strncmp(str, "export", 7) == 0)
// 	// 	return (true);
// 	// else if (ft_strncmp(str, "unset", 6) == 0)
// 	// 	return (true);
// 	else if (ft_strncmp(str, "env", 4) == 0)
// 		return (true);
// 	// else if (ft_strncmp(str, "exit", 5) == 0)
// 	// 	return (true);
// 	else
// 		return (false);
// 	return (true);
// }

int	execute_builtin(char *str, char *args, char **envp)
{
	if (str == NULL)
		return (1);
	if (ft_strncmp(str, "cd", 3) == 0)
		return (builtin_cd(args));
	// else if (ft_strncmp(str, "echo", 5) == 0)
	// 	return (builtin_echo(str, args));
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (builtin_pwd(envp));
	// else if (ft_strncmp(str, "export", 7) == 0)
	// 	return (builtin_export(envp));
	// else if (ft_strncmp(str, "unset", 6) == 0)
	// 	return (builtin_unset(envp));
	else if (ft_strncmp(str, "env", 4) == 0)
		return (builtin_env(envp));
	// else if (ft_strncmp(str, "exit", 5) == 0)
	// 	return (builtin_exit(envp));
	else
		return (1);
	return (0);
}
