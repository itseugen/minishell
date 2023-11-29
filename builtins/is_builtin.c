/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:17:58 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/29 16:33:56 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	str_to_lower(char *cmd);

int	execute_builtin(char **split, t_env *env_list, t_exec **exec)
{
	if (split[0] == NULL)
		return (1);
	if (ft_strncmp(split[0], "cd", 3) == 0)
		return (builtin_cd(split, env_list));
	else if (ft_strncmp(split[0], "echo", 5) == 0)
		return (builtin_echo(split, NULL));
	else if (ft_strncmp(split[0], "pwd", 4) == 0)
		return (builtin_pwd(env_list));
	else if (ft_strncmp(split[0], "export", 7) == 0)
		return (builtin_export(split, env_list));
	else if (ft_strncmp(split[0], "unset", 6) == 0)
		return (builtin_unset(split, env_list));
	else if (ft_strncmp(split[0], "env", 4) == 0)
		return (builtin_env(env_list));
	else if (ft_strncmp(split[0], "exit", 5) == 0)
		return (builtin_exit(split, env_list, exec));
	else
		return (1);
	return (0);
}

/// @brief Returns true if the cmd is a builtin
/// @param cmd the command to check
/// @return true if it is a builtin, otherwise false
bool	is_builtin(char *cmd)
{
	str_to_lower(cmd);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

static void	str_to_lower(char *cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
}
