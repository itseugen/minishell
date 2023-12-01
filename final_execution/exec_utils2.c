/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 05:55:14 by adhaka            #+#    #+#             */
/*   Updated: 2023/12/01 07:25:14 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_dup(int *tmp)
{
	*tmp = dup(0);
	if (*tmp == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
}

void	close_fds(t_exec **exec, int i)
{
	if (exec[i]->in_fd > 2)
		close(exec[i]->in_fd);
	if (exec[i]->out_fd > 2)
		close(exec[i]->out_fd);
}

void	execute_child(int *fd, t_exec *exec, t_env *env, int *tmp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	if (dup2(fd[1], 1) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	if (is_builtin(exec->cmds[0]) == true)
	{
		if (execute_builtin(exec->cmds, env, &exec) == 1)
			exit(1);
		exit(0);
	}
	ex(exec, env, *tmp);
	exit(1);
}

void	execute_last_child(t_exec **exec, t_env *env, int tmp, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ex(exec[i], env, tmp);
	exit(EXIT_FAILURE);
}

void	execute_last_parent(pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_last_exit_status = WEXITSTATUS(status);
	else
		g_last_exit_status = 1;
}
