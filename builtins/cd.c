/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:46:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/15 15:36:03 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	builtin_cd(char **cmds, t_env *env_list)
// {
// 	int		ret;
// 	char	*home_dir;

// 	if (cmds[0] == NULL)
// 		return (1);
// 	if (cmds[1] == NULL || ft_strncmp(cmds[1], "~", 2) == 0)
// 	{
// 		home_dir = get_env_var("HOME", env_list);
// 		if (home_dir == NULL)
// 			return (perror("HOME variable not set"), 1);
// 		ret = chdir(home_dir);
// 	}
// 	else if (cmds[2] != NULL)
// 	{
// 		ft_fprintf(2, "CD: too many arguments!\n");
// 		return (1);
// 	}
// 	else
// 		ret = chdir(cmds[1]);
// 	return (ret);
// }

/// @brief 
/// @param cmds 
/// @param env_list 
/// @throw Could segfault if PWD doesnt exist
/// @return 
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
