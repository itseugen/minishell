/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:05:18 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/26 12:32:02 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//! To be tested
int	unset(char **args, char **envp)
{
	int	i;
	int	e_i;

	i = 0;
	e_i = 0;
	if (args == NULL || envp == NULL)
		return (1);
	while (args[i] != NULL)
	{
		while (envp[e_i] != NULL)
		{
			if (ft_strncmp(envp[e_i], args[i], ft_strlen(args[i])))
			{
				envp[e_i] = "";
				break ;
			}
			e_i++;
		}
		i++;
	}
	return (0);
}
