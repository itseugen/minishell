/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:43:00 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/27 01:33:12 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	executor(t_exec **exec, t_env *env)
// {
// 	int	i;
// 	int	tmp;
// 	int	fd[2];

// 	tmp = dup(0);
// 	i = 0;
// 	while (1)
// 	{
// 		if (!exec[i + 1])
// 		{
// 			if (!fork())
// 			{
// 				ex(exec[i], env, tmp);
// 				exit(1);
// 			}
// 			close(tmp);
// 			while (waitpid(-1, NULL, WUNTRACED) != -1)
// 				;
// 			tmp = dup(0);
// 			break ;
// 		}
// 		else
// 		{
// 			pipe(fd);
// 			if (!fork())
// 			{
// 				close(fd[0]);
// 				dup2(fd[1], 1);
// 				close(fd[1]);
// 				ex(exec[i], env, tmp);
// 				exit(1);
// 			}
// 			close(fd[1]);
// 			close(tmp);
// 			tmp = fd[0];
// 		}
// 		if (exec[i]->in_fd > 2)
// 			close(exec[i]->in_fd);
// 		if (exec[i]->out_fd > 2)
// 			close(exec[i]->out_fd);
// 		i++;
// 	}
// 	close(tmp);
// }
// void	executor(t_exec **exec, t_env *env)
// {
//     int	i;
//     int	tmp;
//     int	fd[2];
//     pid_t	pid;

//     tmp = dup(0);
//     if (tmp == -1)
//     {
//         perror("dup");
//         exit(EXIT_FAILURE);
//     }
//     i = 0;
//     while (1)
//     {
//         if (!exec[i + 1])
//         {
//             pid = fork();
//             if (pid == -1)
//             {
//                 perror("fork");
//                 exit(EXIT_FAILURE);
//             }
//             if (pid == 0)
//             {
//                 ex(exec[i], env, tmp);
//                 exit(1);
//             }
//             close(tmp);
//             while (waitpid(pid, NULL, WUNTRACED) != -1)
//                 ;
//             tmp = dup(0);
//             if (tmp == -1)
//             {
//                 perror("dup");
//                 exit(EXIT_FAILURE);
//             }
//             break ;
//         }
//         else
//         {
//             if (pipe(fd) == -1)
//             {
//                 perror("pipe");
//                 exit(EXIT_FAILURE);
//             }
//             pid = fork();
//             if (pid == -1)
//             {
//                 perror("fork");
//                 exit(EXIT_FAILURE);
//             }
//             if (pid == 0)
//             {
//                 close(fd[0]);
//                 if (dup2(fd[1], 1) == -1)
//                 {
//                     perror("dup2");
//                     exit(EXIT_FAILURE);
//                 }
//                 close(fd[1]);
//                 ex(exec[i], env, tmp);
//                 exit(1);
//             }
//             close(fd[1]);
//             close(tmp);
//             tmp = fd[0];
//         }
//         if (exec[i]->in_fd > 2)
//             close(exec[i]->in_fd);
//         if (exec[i]->out_fd > 2)
//             close(exec[i]->out_fd);
//         i++;
//     }

// void	execute_last_command(t_exec **exec, t_env *env, int tmp, int i)
// {
//     pid_t	pid;

//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid == 0)
//     {
//         if (is_builtin(exec[i]->cmds[0]))
//             execute_builtin(exec[i], env);
//         else
//             ex(exec[i], env, tmp);
//         exit(1);
//     }
//     close(tmp);
//     while (waitpid(pid, NULL, WUNTRACED) != -1)
//         ;
// }

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

void execute_command(t_exec *exec, t_env *env, int *tmp, int *fd)
{
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(fd[0]);
        if (dup2(fd[1], 1) == -1) {
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

// void	execute_command(t_exec **exec, t_env *env, int *tmp, int *fd, int i)
// {
//     pid_t	pid;

//     if (pipe(fd) == -1)
//     {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid == 0)
//     {
//         close(fd[0]);
//         if (dup2(fd[1], 1) == -1)
//         {
//             perror("dup2");
//             exit(EXIT_FAILURE);
//         }
//         close(fd[1]);
//         if (is_builtin(exec[i]->cmds[0]))
//             execute_builtin(exec[i], env);
//         else
//             ex(exec[i], env, *tmp);
//         exit(1);
//     }
//     close(fd[1]);
//     close(*tmp);
//     *tmp = fd[0];
// }

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

// int	execute_builtin(t_exec *exec, t_env *env)
// {
//     if (ft_strncmp(exec->cmds[0], "cd", 2) == 0)
//         builtin_cd(exec, env);
//     else if (ft_strncmp(exec->cmds[0], "echo", 4) == 0)
//         builtin_echo(exec, env);
// 	else if (ft_strncmp(exec->cmds[0], "pwd", 4) == 0)
//         builtin_echo(exec, env);
// 	else if (ft_strncmp(exec->cmds[0], "env", 4) == 0)
//         builtin_pwd(env);
// 	else if (ft_strncmp(exec->cmds[0], "export", 4) == 0)
//         builtin_echo(exec, env);
// 	else if (ft_strncmp(exec->cmds[0], "unset", 4) == 0)
//         builtin_echo(exec, env);
// 	else if (ft_strncmp(exec->cmds[0], "exit", 4) == 0)
//         builtin_echo(exec, env);
// 	else 
// 		return (-1);
// 	return (0);
// }

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

char	*get_cmd_path(char *cmd, char **path)
{
    char	*correct_path;
    int		i;
    char	*tmp;

    i = 0;
    while (path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        correct_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(correct_path, X_OK | F_OK) == 0)
            break ;
        free(correct_path);
        correct_path = NULL;
        i++;
    }
    return (correct_path);
}

char	*correct(t_exec *exec, char **envp)
{
    char	**path;
    char	*correct_path;

    if (ft_strchr(exec->cmds[0], '/') != NULL)
    {
        if (access(exec->cmds[0], X_OK | F_OK) == 0)
            return (ft_strdup(exec->cmds[0]));
        else
            return (NULL);
    }

    path = get_path(envp);
    correct_path = get_cmd_path(exec->cmds[0], path);
    return (correct_path);
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
