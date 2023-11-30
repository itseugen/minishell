/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:50:09 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/29 19:48:16 by eweiberl         ###   ########.fr       */
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

int get_exit_signal(void)
{
    return g_last_exit_status;
}