/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:43:00 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/26 06:26:31 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_exec **exec, t_env *env)
{
	int	i;
	int	tmp;
	int	fd[2];

	tmp = dup(0);
	i = 0;
	while (1)
	{
		if (!exec[i + 1])
		{
			if (!fork())
			{
				ex(exec[i], env, tmp);
				exit(1);
			}
			close(tmp);
			while (waitpid(-1, NULL, WUNTRACED) != -1)
				;
			tmp = dup(0);
			break ;
		}
		else
		{
			pipe(fd);
			if (!fork())
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
				ex(exec[i], env, tmp);
				exit(1);
			}
			close(fd[1]);
			close(tmp);
			tmp = fd[0];
		}
		if (exec[i]->in_fd > 2)
			close(exec[i]->in_fd);
		if (exec[i]->out_fd > 2)
			close(exec[i]->out_fd);
		i++;
	}
	close(tmp);
}

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

char	*correct(t_exec *exec, char **envp)
{
	char	**path;
	char	*correct_path;
	int		i;
	char	*tmp;

	i = 0;
	path = get_path(envp);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		correct_path = ft_strjoin(tmp, exec->cmds[0]);
		free(tmp);
		if (access(correct_path, X_OK | F_OK) == 0)
			break ;
		free(correct_path);
		correct_path = NULL;
		i++;
	}
	return (correct_path);
}

void	ex(t_exec *exec, t_env *env, int tmp)
{
	char *path;
	char **envp;

	envp = get_env(env);
	path = correct(exec, envp);
	dup2(tmp, 0);
	close(tmp);
	if (exec->in_fd > 2)
	{
		dup2(exec->in_fd, 0);
		close(exec->in_fd);
	}
	if (exec->out_fd > 2)
	{
		dup2(exec->out_fd, 1);
		close(exec->out_fd);
	}
	execve(path, exec->cmds, envp);
}
