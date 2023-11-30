/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:08:44 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/29 19:51:26 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* In this function: add a function that frees the executable.
* make sure this free_exec function frees the struct completely
* and also frees the char **args etc.
! In execute_command AND execute_last_cmd replace NULL with the
! t_exec struct so it can be freed accordingly
! Also put the free_exec function at the bottom
! of the while loop in main!
*/

/// @brief Exits the shell, if called in a child, exits the child
/// @param split the arguments to the function
/// @param env_list the environment list
/// @param executable the executable to free
/// @return exits with 0, or the exit code given as argument
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
	if (executable != NULL)
		free_exec_array(executable);
	clear_history();
	(void)executable;
	exit(exit_code);
}
