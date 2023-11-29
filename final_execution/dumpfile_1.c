/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumpfile_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:01:28 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/29 06:02:26 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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


