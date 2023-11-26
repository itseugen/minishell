/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:44:43 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/26 22:18:33 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

///@brief Redirects a file into a command, writes the command to a pipe
int	first_child(int *pipe_fd, t_token *token, t_env *env_list)
{
	char	**split;
	char	**envp;

	close(pipe_fd[0]);
	if (dup2(token->parser.fd, STDIN_FILENO) == -1)
		return (perror("dup2 fail"), close(pipe_fd[1]), 1);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2 fail"), close(pipe_fd[1]), 1);
	close(pipe_fd[1]);
	token = token->next;
	split = ft_split_minishell(token->cmd, ' ');
	envp = env_get_envp(env_list);
	if (split == NULL || rem_quotes(split) == 1)
		return (close(pipe_fd[1]), 1);
	if (is_builtin(split[0]) == true)
		execute_builtin(split, env_list, token->cmd);
	else if (execute_cmd(split, envp) == 1)
	{
		free_strings((void **)split);
		free(envp);
		exit(1);
	}
	free_strings((void **)split);
	free(envp);
	exit(0);
	return (0);
}

///@brief Redirects the output of a command into a file
int	last_child(int *pipe_fd, t_token *token, t_env *env_list)
{
	char	**split;
	char	**envp;

	close(pipe_fd[1]);
	if (dup2(token->next->parser.fd, STDOUT_FILENO) == -1)
		return (perror("dup2 fail"), close(pipe_fd[0]), 1);
	close(pipe_fd[0]);
	split = ft_split_minishell(token->cmd, ' ');
	envp = env_get_envp(env_list);
	if (split == NULL || rem_quotes(split) == 1)
		return (close(pipe_fd[1]), 1);
	if (is_builtin(split[0]) == true)
		execute_builtin(split, env_list, token->cmd);
	else if (execute_cmd(split, envp) == 1)
	{
		free_strings((void **)split);
		free(envp);
		exit(1);
	}
	free_strings((void **)split);
	free(envp);
	exit(0);
	return (0);
}

///@brief redirects the output of a command into a pipe
int	middle_child(int *pipe_fd, t_token *token, t_env *env_list)
{
	char	**split;
	char	**envp;

	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2 fail"), close(pipe_fd[1]), 1);
	close(pipe_fd[1]);
	split = ft_split_minishell(token->cmd, ' ');
	envp = env_get_envp(env_list);
	if (split == NULL || rem_quotes(split) == 1)
		return (close(pipe_fd[1]), 1);
	if (is_builtin(split[0]) == true)
		execute_builtin(split, env_list, token->cmd);
	else if (execute_cmd(split, envp) == 1)
	{
		free_strings((void **)split);
		free(envp);
		exit(1);
	}
	free_strings((void **)split);
	free(envp);
	exit(0);
	return (0);
}
