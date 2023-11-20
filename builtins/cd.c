/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:46:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/20 13:20:09 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//! CHANGE SO IT WORKS WITH PWD UNSET. IT SHOULD ONLY CHANGE PWD/OLDPWD IF THEY EXIST

/// @brief Changes the directory and updates OLDPWD and PWD
/// @param cmds the arguments to cd
/// @param env_list the environment list
/// @throw Could segfault if PWD doesnt exist
/// @return 0 on succes, 1 on malloc fail or wrong command
int	builtin_cd(char **cmds, t_env *env_list)
{
	char	*path;
	char	*new_pwd;

	if (cmds[0] == NULL)
		return (1);
	if (cmds[1] == NULL || ft_strncmp(cmds[1], "~", 2) == 0)
		path = get_env_var("HOME", env_list);
	else if (cmds[2] == NULL)
		path = cmds[1];
	else
		return (ft_fprintf(2, "cd: too many args\n"), 1);
	if (replace_env_var("OLDPWD=", get_env_var("PWD", env_list), env_list) == 1)
		return (1);
	chdir(path);
	new_pwd = getcwd(NULL, 0);
	if (replace_env_var("PWD=", new_pwd, env_list) == 1)
		return (free(new_pwd), 1);
	free(new_pwd);
	return (0);
}
