/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 04:21:25 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/23 11:05:33 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_counter(t_token *tokens)
{
	int	n_cmds;

	n_cmds = 1;
	while (tokens)
	{
		//! Potential wrong use of strncmp (len = 2), also lexer identifies pipes -> in this case expanded variables containing a pipe symbol could be identified wrong
		if (!ft_strncmp(tokens->cmd, "|", 1))
			n_cmds++;
		tokens = tokens->next;
	}
	return (n_cmds);
}

t_exec	**commands_for_exec(t_token *tokens)
{
	int		n_cmds;
	int		i;
	t_exec	**exec;

	n_cmds = cmd_counter(tokens);
	i = 0;
	//! Why not calloc?
	exec = malloc(sizeof(t_exec *) * n_cmds + 1);
	if (!exec)
		return (NULL);
	while (tokens)
	{
		if (tokens->operation == CMD)
		{
			exec[i] = (t_exec *)malloc(sizeof(t_exec));
			if (!exec[i])
				return (free_strings((void **)exec), NULL);
			fill(exec[i], tokens);
			i++;
		}
		tokens = tokens->next;
	}
	exec[i] = NULL;
	return (exec);
}

void	fill(t_exec *exec, t_token *tokens)
{
	exec->cmds = tokens->table->cmd;
	exec->in_fd = tokens->table->in_fd;
	exec->out_fd = tokens->table->out_fd;
}

	// i = 0;
	// while (exec[i])
	// {
	// 	printf("%s------%d\n", exec[i]->cmds[0], exec[i]->in_fd);
	// 	i++;
	// }
