/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:50:09 by eweiberl          #+#    #+#             */
/*   Updated: 2023/12/01 04:24:13 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Checks if the expander is in '"' right now
/// @param in_quotes
/// @return true if it is, false if it isnt
bool	set_in_quotes(bool in_quotes)
{
	if (in_quotes == false)
		in_quotes = true;
	else
		in_quotes = false;
	return (in_quotes);
}

int	get_exit_signal(void)
{
	return (g_last_exit_status);
}
