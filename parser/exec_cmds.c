/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 04:21:25 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/25 04:57:14 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Counts the number of commands in a given token list.
/// @param tokens
/// @return (n_cmds) no. of commands
int	cmd_counter(t_token *tokens)
{
	int	n_cmds;

	n_cmds = 1;
	while (tokens)
	{
		//! Potential wrong use of strncmp (len = 2), also lexer identifies pipes -> in this case expanded variables containing a pipe symbol could be identified wrong
		//answer: the lexer is turning a pipe into a token so we just check if it's a pipe then we increment the no. of cmds
		//		  (the whole string before the pipe is taken as a n_cmd and everything else after is taken as a n_cmd, if there are redirections they are handled beforehand so not a notproblem with that).
		if (!ft_strncmp(tokens->cmd, "|", 1))
			n_cmds++;
		tokens = tokens->next;
	}
	return (n_cmds);
}

/// @brief Allocates an array of t_exec* pointers to represent individual commands for execution
/// @param tokens
/// @return table with the commands (the array of t_exec* pointers)
t_exec	**commands_for_exec(t_token *tokens)
{
	int		n_cmds;
	int		i;
	t_exec	**exec;

	n_cmds = cmd_counter(tokens);
	i = 0;
	//! Why not calloc?
	// Answer: way more used to malloc, doesn't causes any leaks where i used it so should be okay.
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

/// @brief Populates a t_exec structure with information from a t_token structure
/// @param exec
/// @param tokens
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
