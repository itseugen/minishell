/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 04:21:25 by adhaka            #+#    #+#             */
/*   Updated: 2023/12/01 04:24:13 by adhaka           ###   ########.fr       */
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
		if (tokens->operation == PIPE)
			n_cmds++;
		tokens = tokens->next;
	}
	return (n_cmds);
}


/// @brief Allocates an array of t_exec* pointer
///		   to represent individual commands for execution
/// @param tokens
/// @return table with the commands (the array of t_exec* pointers)
t_exec	**commands_for_exec(t_token *tokens)
{
	int		n_cmds;
	int		i;
	t_exec	**exec;

	n_cmds = cmd_counter(tokens);
	i = 0;
	exec = ft_calloc(n_cmds + 1, sizeof(t_exec *));
	if (!exec)
		return (NULL);
	while (tokens)
	{
		if (tokens->operation == CMD)
		{
			exec[i] = (t_exec *)ft_calloc(1, sizeof(t_exec));
			if (!exec[i])
				return (free_exec_array(exec), NULL);
			fill(exec[i], tokens);
			i++;
		}
		tokens = tokens->next;
	}
	exec[i] = NULL;
	return (exec);
}

/// @brief Populates a t_exec
/// structure with information from a t_token structure
/// @param exec
/// @param tokens
void	fill(t_exec *exec, t_token *tokens)
{
	exec->cmds = tokens->table->cmd;
	exec->in_fd = tokens->table->in_fd;
	exec->out_fd = tokens->table->out_fd;
}

/// @brief Frees the array of t_exec* pointers
/// @param exec
void	free_exec_array(t_exec **exec)
{
	int	i;

	i = 0;
	if (exec == NULL)
		return ;
	while (exec[i] != NULL)
	{
		if (exec[i]->cmds != NULL)
			free_strings((void **)exec[i]->cmds);
		i++;
	}
	free(exec);
	exec = NULL;
}


	// i = 0;
	// while (exec[i])
	// {
	// 	printf("%s------%d\n", exec[i]->cmds[0], exec[i]->in_fd);
	// 	i++;
	// }
