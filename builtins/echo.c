/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:23:40 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/29 19:53:17 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief prints the input to the terminal
/// @param split The arguments and what should be printed
/// @param str a remainder of an old version, should be NULL
/// @return 1 on fail, otherwise 0
int	builtin_echo(char **split, char *str)
{
	int	i;

	(void)str;
	i = 1;
	if (ft_strncmp(split[0], "echo", 5) != 0)
		return (1);
	if (split[1] == NULL)
		return (printf("\n"), 0);
	if (ft_strncmp(split[1], "-n", 3) == 0)
		i++;
	while (split[i] != NULL)
	{
		printf("%s", split[i]);
		i++;
		if (split[i] != NULL)
			printf(" ");
	}
	if (ft_strncmp(split[1], "-n", 3) != 0)
		printf("\n");
	return (0);
}
