/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:33 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/22 15:13:31 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	read_terminal(t_env *env_list, int *pipe_fd, char *delim);

//! Note: While heredocs should be expanded, the env get expanded even in ''
//! While imo dont have to implement it, if we want to, we just copy the expandr
//!and change it to expand always

//! Expand only AFTER comparing to delimiter

/// @brief handle a heredoc and provides it to the pipe provided
/// @param env_list the env_list
/// @param pipe_fd A initialised pipe to write to
/// @param split The arguments to the function
/// @return 0 on success, 1 on malloc/etc failure
int	here_doc(t_env *env_list, int *pipe_fd, char **split)
{
	if (ft_strncmp(split[0], "<<", 3) != 0)
		return (1);
	if (split[1] == NULL)
		return (ft_putstr_fd("<<: no delimiter given\n", 2), 1);
	if (read_terminal(env_list, pipe_fd, split[1]) != 0)
		return (1);
	return (0);
}

/// @brief Reads the terminal till delim is reached
/// @param env_list
/// @param pipe_fd the pipe to write to
/// @param delim the limiter to stop reading at
/// @return 0, 1 if malloc fails
static int	read_terminal(t_env *env_list, int *pipe_fd, char *delim)
{
	char	*line;

	line = readline("> ");
	while (line != NULL && ft_strncmp(line, delim, ft_strlen(delim) + 1) != 0)
	{
		line = expander(line, env_list);
		if (line == NULL)
			return (close(pipe_fd[1]), 1);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(pipe_fd[1]);
	if (line != NULL)
		free(line);
	return (0);
}
