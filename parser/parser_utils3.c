/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:57:04 by adhaka            #+#    #+#             */
/*   Updated: 2023/12/01 07:00:26 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_maker_extension(t_token *tokens, t_token *tmp)
{
	if (tokens->cmd[0] == '<')
	{
		if (in_out(tokens->cmd, tmp, 0) == -1)
			return (-1);
		tmp->table->in_fd = ft_open(tmp->table->input_file, 0);
		if (tmp->table->in_fd == -1)
			return (-1);
	}
	if (tokens->cmd[0] == '>')
	{
		if (in_out(tokens->cmd, tmp, 1) == -1)
			return (-1);
		if (tokens->cmd[1] == '>')
			tmp->table->out_fd = ft_open(tmp->table->output_file, 2);
		else
			tmp->table->out_fd = ft_open(tmp->table->output_file, 1);
		if (tmp->table->out_fd == -1)
			return (-1);
	}
	return (0);
}
