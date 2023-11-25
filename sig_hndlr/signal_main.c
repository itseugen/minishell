/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:45:48 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/25 01:10:15 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_d(void)
{
	// mini_exit(NULL);
}

void	ctrl_bs(void)
{
	rl_on_new_line();
	rl_redisplay();
}

void	sig_type(int sig)
{
	if (sig == SIGINT)
		ctrl_c();
	else if (sig == SIGQUIT)
		ctrl_bs();
}

void	clear_sigargs(void)
{
	struct termios	arg;

	tcgetattr(1, &arg);
	arg.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &arg);
}

// int	custom_exit(t_token *tokens)
// {
// 	t_command	*cmd;

// 	if (tokens != NULL && tokens->table != NULL)
// 	{
// 		cmd = tokens->table;
// 		if (cmd->cmd != NULL && cmd->cmd[0] != NULL)
// 		{
// 			if (cmd->cmd[0][0] == '\0')
// 			{
// 				fprintf(STDERR, "bash: exit: : numeric argument required\n");
// 				return (free_command(cmd), exit(255), 1);
// 			}
// 			if (cmd->cmd[1] != NULL)
// 			{
// 				fprintf(STDERR, "exit: too many arguments\n");
// 				return (free_command(cmd), exit(1), 0);
// 			}
// 			if (atoi(cmd->cmd[0]) == 0 && cmd->cmd[0][0] != '0')
// 			{
// 				fprintf(STDERR, "exit: %s: numeric argument required\n", cmd->cmd[0]);
// 				return (free_command(cmd), exit(255), 0);
// 			}
// 			free_command(cmd);
// 			return (exit(atoi(cmd->cmd[0])), 0);
// 		}
// 	}
// 	return (free_command(cmd), exit(0), 0);
// }

// void	free_command(t_command *cmd)
// {
// 	int	i;

// 	i = 0;
// 	if (cmd == NULL)
// 		return (NULL);
// 	free(cmd->cmd_name);
// 	if (cmd->cmd != NULL)
// 	{
// 		while (cmd->cmd[i] != NULL)
// 		{
// 			free(cmd->cmd[i]);
// 			i++;
// 		}
// 		free(cmd->cmd);
// 	}
// 	free(cmd->input_file);
// 	free(cmd->output_file);
// 	free(cmd);
// }
