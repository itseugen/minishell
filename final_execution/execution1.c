/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:43:00 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/29 07:09:33 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_last_command(t_exec **exec, t_env *env, int tmp, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		ex(exec[i], env, tmp);
		exit(1);
	}
	close(tmp);
	while (waitpid(pid, NULL, WUNTRACED) != -1)
		;
}

void	execute_command(t_exec *exec, t_env *env, int *tmp, int *fd)
{
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		ex(exec, env, *tmp);
		exit(1);
	}
	close(fd[1]);
	close(*tmp);
	*tmp = fd[0];
}

void	executor(t_exec **exec, t_env *env)
{
	int	i;
	int	tmp;
	int	fd[2];

	handle_dup(&tmp);
	i = 0;
	while (1)
	{
		if (!exec[i + 1])
		{
			execute_last_command(exec, env, tmp, i);
			handle_dup(&tmp);
			break ;
		}
		else
		{
			execute_command(exec[i], env, &tmp, fd);
		}
		close_fds(exec, i);
		i++;
	}
}


void	ex(t_exec *exec, t_env *env, int tmp)
{
	char	*path;
	char	**envp;

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
	if (execve(path, exec->cmds, envp) == -1)
	{
		ft_putstr_fd(exec->cmds[0], 2);
		ft_putstr_fd(": command does not exist\n", 2);
		exit(EXIT_FAILURE);
	}
}
