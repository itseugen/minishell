/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:43:15 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/24 17:19:28 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirect(char *cmd)
{
	if (ft_strncmp(cmd, "<", 2) == 0)
		return (true);
	if (ft_strncmp(cmd, ">", 2) == 0)
		return (true);
	if (ft_strncmp(cmd, ">>", 3) == 0)
		return (true);
	return (false);
}
