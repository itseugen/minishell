/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:48:50 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/13 16:03:05 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//! CHANGE SPLIT OR ANOTHER FUNCTION TO REMOVE QUOTES!!!!

int	execute_first(t_token *tokens, char **envp, int *pipfd)
{
	pid_t	pro_id;

	pro_id = fork();
	if (pro_id != 0)
		return (0);
	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) == -1)
		return (perror("dup2 fail1"), close(pipfd[1]), 1);
	close(pipfd[1]);
	if (executor(tokens, envp) == 1)
		exit(1);
	exit(0);
}

int	last_child(t_token *tokens, char **envp, int *pipfd)
{
	pid_t	pro_id;

	pro_id = fork();
	if (pro_id != 0)
		return (0);
	close(pipfd[1]);
	if (dup2(pipfd[0], STDIN_FILENO) == -1)
		return (perror("dup2 fail2"), close(pipfd[0]), 1);
	close(pipfd[0]);
	if (executor(tokens, envp) == 1)
		exit(1);
	exit(0);
}

// int	middle_child(int *pipe_fd, t_pipe pipe_x, char *cmd)
// {
// 	close(pipe_fd[0]);
// 	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 		return (perror("dup2 fail"),
// 			close(pipe_fd[1]), clean_exit(pipe_x, 1), 1);
// 	close(pipe_fd[1]);
// 	close(pipe_x.fd_in);
// 	close(pipe_x.fd_out);
// 	if (execute_cmd(cmd, pipe_x) == 1)
// 		clean_exit(pipe_x, 1);
// 	clean_exit(pipe_x, 0);
// 	return (0);
// }
