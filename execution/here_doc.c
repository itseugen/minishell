/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:33 by eweiberl          #+#    #+#             */
/*   Updated: 2023/12/01 06:48:33 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	read_terminal(t_env *env_list, int fd, char *delim);

/// @brief handle a heredoc and provides it to the pipe provided
/// @param env_list the env_list
/// @param pipe_fd A initialised pipe to write to
/// @param split The arguments to the function
/// @return 0 on success, 1 on malloc/etc failure
int	here_doc(t_env *env_list, char *delim)
{
	int	fd;

	if (delim == NULL)
		return (ft_putstr_fd("<<: no delimiter given\n", 2), 1);
	fd = open(".hd.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		return (ft_putstr_fd("<<: open failed\n", 2), 1);
	if (read_terminal(env_list, fd, delim) != 0)
	{
		close(fd);
		ft_putstr_fd("<<: malloc failed while reaing the termial\n", 2);
		return (1);
	}
	close(fd);
	fd = open(".hd.txt", O_RDONLY);
	unlink(".hd.txt");
	return (fd);
}

/// @brief Reads the terminal till delim is reached
/// @param env_list
/// @param pipe_fd the pipe to write to
/// @param delim the limiter to stop reading at
/// @return 0, 1 if malloc fails
static int	read_terminal(t_env *env_list, int fd, char *delim)
{
	char	*line;

	line = readline("> ");
	while (line != NULL && ft_strncmp(line, delim, ft_strlen(delim) + 1) != 0)
	{
		line = expander(line, env_list, 0, false);
		if (line == NULL)
			return (1);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line != NULL)
		free(line);
	return (0);
}
