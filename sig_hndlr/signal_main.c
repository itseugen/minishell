/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:45:48 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/30 07:22:39 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief handler fucntion for ctrl + c signal, Prints a newline.
/// @param (void)
/// @return No return value
void	ctrl_c(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

/// @brief handler function for ctrl + \,
			//Exits shell by sending SIGQUIT singal.
/// @param (void)
/// @return No return value
void	ctrl_bs(void)
{
	rl_on_new_line();
	rl_redisplay();
}

/// @brief handler handler function to check type of signal,
			//Exits shell.
/// @param sig(int)
/// @return No return value
void	sig_type(int sig)
{
	if (sig == SIGINT)
		ctrl_c();
	else if (sig == SIGQUIT)
		ctrl_bs();
}

/// @brief handler fucntion for signals,
			// stops the shell from printing ctrl^c.
/// @param (void)
/// @return No return value
void	clear_sigargs(void)
{
	struct termios	arg;

	tcgetattr(1, &arg);
	arg.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &arg);
}
