/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:50:09 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/29 18:51:42 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	set_in_quotes(bool in_quotes)
{
	if (in_quotes == false)
		in_quotes = true;
	else
		in_quotes = false;
	return (in_quotes);
}
