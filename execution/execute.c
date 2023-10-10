/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:26:58 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/10 15:58:06 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cmd_path(char *cmd, char **envp);
static char	*get_cmd(char *path, char *cmd);

int	execute_cmd(char *cmd, char **envp)
{
	char	*cmds[4];
	char	*path;

	path = get_cmd_path(cmd, envp);
	printf("%s\n", path);
	// cmds[0] = path;
	// cmds[1] = "-c";
	// cmds[2] = cmd;
	// cmds[3] = NULL;
	// if (execve(path, cmds, envp) == -1)
	// 	return (free(path), perror("execv"), 1);
	free(path);
	return (0);
}

static char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path;
	char	*cmd_first;
	char	*cmd_path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (path == NULL)
		return (NULL);
	cmd_first = ft_split(cmd, ' ');
	if (cmd_first == NULL)
		return (perror("ft_split fail"), NULL);
	cmd_path = get_cmd(path, cmd_first[0]);
	free(cmd_first);
	return (cmd_path);
}

static char	*get_cmd(char *path, char *cmd)
{
	char	**dir;
	char	*cmd_dir;
	char	buf[1024];
	int		i;
	char	*cmd_path;

	cmd_dir = ft_strjoin("/", cmd);
	dir = ft_split(path, ':');
	if (dir == NULL || cmd_dir == NULL)
		return (perror("ft_split fail"), NULL);
	i = 0;
	while (dir[i] != NULL)
	{
		ft_strlcpy(buf, dir[i], 1024);
		ft_strlcat(buf, cmd_dir, 1024);
		if (access(buf, X_OK) == 0)
		{
			cmd_path = ft_strdup(buf);
			break ;
		}
		i++;
	}
	free(cmd_dir);
	free(dir);
	return (cmd_path);
}
