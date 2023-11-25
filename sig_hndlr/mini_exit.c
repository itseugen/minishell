/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:25:21 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/25 05:12:03 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//i'm having problems writing this since i have to itrgrate it with the bultins
	// also we would need the is_builtin check.
	//if you have some time today go through this one and modify it the way you want to.
	// I'll write and start working on the execution.
/// @brief exit builtin
/// @param tokens
/// @return
int	mini_exit(t_token *tokens)
{
	t_command	*cmd;

	cmd = NULL;
	if (tokens != NULL && tokens->table != NULL)
	{
		cmd = tokens->table;
		if (cmd->cmd_name != NULL)
		{
			if (cmd->cmd_name[0] == '\0')
			{
				ft_fprintf(2, "bash: exit: : numeric argument required\n");
				return (free_command(cmd), exit(255), 1);
			}
			if (cmd->cmd[1] != NULL)
			{
				ft_fprintf(2, "exit: too many arguments\n");
				return (free_command(cmd), exit(1), 0);
			}
			if (ft_atoi(cmd->cmd_name) == 0 && cmd->cmd_name[0] != '0')
			{
				ft_fprintf(2, "exit: %s: numeric argument required\n", cmd->cmd_name);
				return (free_command(cmd), exit(255), 0);
			}
			free_command(cmd);
			return (exit(ft_atoi(cmd->cmd_name)), 0);
		}
	}
	if (cmd == NULL)
	{
		free_command(cmd);
	}
	return (exit(0), 0);
}

/// @brief function to free the command table
/// @param cmd
void	free_command(t_command *cmd)
{
	int	i;

	i = 0;
	free(cmd->cmd_name);
	if (cmd->cmd != NULL)
	{
		while (cmd->cmd[i] != NULL)
		{
			free(cmd->cmd[i]);
			i++;
		}
		free(cmd->cmd);
	}
	free(cmd->input_file);
	free(cmd->output_file);
	free(cmd);
}
