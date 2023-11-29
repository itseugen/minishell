/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 05:55:14 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/29 05:55:30 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
