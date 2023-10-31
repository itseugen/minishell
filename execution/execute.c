/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:26:58 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/31 17:01:38 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cmd_path(char *cmd, char **envp);
static char	*get_cmd(char *path, char *cmd);
static void	free_split(char **strings);

/// @brief Executes a command via path
/// @param cmd NULL terminated array of strings
/// @param envp the envp
/// @return 1 on fail, 0 on success
int	execute_cmd(char **cmd, char **envp)
{
	char	*path;

	path = get_cmd_path(cmd[0], envp);
	if (path == NULL)
		return (perror("no path"), 1);
	if (execve(path, cmd, envp) == -1)
		return (free(path), ft_fprintf(STDERR_FILENO,
				"minishell: cmd not found: %s\n", cmd[0]), 1);
	free(path);
	return (0);
}

/// @brief Gets the Path variable, calls another func
/// @param cmd the identifier of the cmd array
/// @param envp 
/// @return returns the path to the command or NULL
static char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path;
	char	*cmd_path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i] != NULL)
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
	cmd_path = get_cmd(path, cmd);
	return (cmd_path);
}

/// @brief Searches the path variable to a path to command
/// @param path 
/// @param cmd 
/// @return Path to command or NULL
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
	cmd_path = NULL;
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
	return (free(cmd_dir), free_split(dir), cmd_path);
}

static void	free_split(char **strings)
{
	size_t	i;

	i = 0;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
