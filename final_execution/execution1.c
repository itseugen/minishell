/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:43:00 by adhaka            #+#    #+#             */
/*   Updated: 2023/12/01 07:26:48 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_for_children(int status);

void	execute_last_command(t_exec **exec, t_env *env, int tmp, int i)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (is_builtin(exec[i]->cmds[0]) == true)
	{
		execute_builtin(exec[i]->cmds, env, exec);
		return ;
	}
	block_signal();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		execute_last_child(exec, env, tmp, i);
	else
		execute_last_parent(pid, status);
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
	block_signal();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		execute_child(fd, exec, env, tmp);
	close(fd[1]);
	close(*tmp);
	*tmp = fd[0];
}

void	executor(t_exec **exec, t_env *env)
{
	int	i;
	int	tmp;
	int	fd[2];
	int	status;

	status = 0;
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
	wait_for_children(status);
}

static void	wait_for_children(int status)
{
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);
		else
			g_last_exit_status = 1;
	}
}

void	ex(t_exec *exec, t_env *env, int tmp)
{
	char	*path;
	char	**envp;

	envp = env_get_envp(env);
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
		free(envp);
		exit(127);
	}
}
