/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:59:38 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/09 18:07:21 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(t_token *tokens, char **envp)
{
	t_token	*current;
	int		pipfd[2];
	char	*test;

	current = tokens;
	// while (current != NULL)
	// {
		if (pipe(pipfd) == -1)
			return (ft_fprintf(2, "pipe fail\n"), 1);
		close(pipfd[1]);
		executor(pipfd, current, envp);
		// if (current->next != NULL)
		// 	if (dup2(pipfd[0], STDIN_FILENO) == -1)
		// 		return (ft_fprintf(2, "dup2 fail\n"), 1);
		// close(pipfd[0]);
		test = get_next_line(pipfd[0]);
		while (test != NULL)
		{
			printf("%s", test);
			free(test);
			test = get_next_line(pipfd[0]);
		}
		close(pipfd[0]);
		// current = current->next;
	// }
}

int	executor(int *pipfd, t_token *tokens, char **envp)
{
	char	**split;
	pid_t	pro_id;

	close(pipfd[1]);
	// if (dup2(pipfd[0], STDOUT_FILENO) == -1)
	// 	return (ft_fprintf(2, "dup2 fail in executor1\n"), 1);
	close(pipfd[0]);
	if (tokens->operation == CMD)
	{
		split = ft_split_minishell(tokens->cmd, ' ');
		if (split == NULL)
			return (ft_fprintf(2, "malloc fail in executor2\n"));
		pro_id = fork();
		if (pro_id == 0)
			if (execute_cmd(split, envp) == 1)
				exit(1);
		free_strings((void **)split);
	}
	// else if (tokens->operation == BUILTIN)
	// 	//execute builtin
	return (0);
}
