/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:08:44 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/29 16:38:03 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_exit(char **split, t_env *env_list, t_exec **executable)
{
	int	exit_code;
	int	i;

	if (ft_strncmp(split[0], "exit", 5) != 0)
		return (1);
	exit_code = 0;
	i = 1;
	if (split[1] != NULL)
	{
		if (ft_isstr(split[1], ft_isdigit) == 1)
		{
			exit_code = ft_atoi(split[1]);
			if (exit_code > 255)
				exit_code = exit_code % 256;
		}
		else
			ft_fprintf(2, "exit: %s: numeric argument needed\n", split[1]);
		while (split[++i] != NULL)
			ft_fprintf(2, "exit: %s: too many arguments\n", split[i]);
	}
	free_env_struct(&env_list);
	// free_exec();
	clear_history();
	(void)executable;
	exit(exit_code);
}
