/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 05:53:45 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/29 05:55:01 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_env(t_env *env)
{
	char	**envp;
	t_env	*head;
	int		i;

	head = env;
	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	env = head;
	while (env)
	{
		envp[i] = ft_strdup(env->var);
		i++;
		env = env->next;
	}
	envp[i] = 0;
	return (envp);
}

char	**get_path(char	**envp)
{
	char	*tmp;
	char	**path;
	int		i;

	i = 0;
	tmp = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			tmp = ft_substr(envp[i], 0, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	path = ft_split(tmp + 5, ':');
	free(tmp);
	tmp = NULL;
	return (path);
}

char	*get_cmd_path(char *cmd, char **path)
{
	char	*correct_path;
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		correct_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(correct_path, X_OK | F_OK) == 0)
			break ;
		free(correct_path);
		correct_path = NULL;
		i++;
	}
	return (correct_path);
}

char	*correct(t_exec *exec, char **envp)
{
	char	**path;
	char	*correct_path;

	if (ft_strchr(exec->cmds[0], '/') != NULL)
	{
		if (access(exec->cmds[0], X_OK | F_OK) == 0)
			return (ft_strdup(exec->cmds[0]));
		else
			return (NULL);
	}

	path = get_path(envp);
	correct_path = get_cmd_path(exec->cmds[0], path);
	return (correct_path);
}
