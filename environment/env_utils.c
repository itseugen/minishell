/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:00:56 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/14 16:01:22 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Prints the t_env struct
/// @param environment_list the struct to print
void	t_print_env_struct(t_env *environment_list)
{
	t_env	*current;

	current = environment_list;
	if (current == NULL)
	{
		ft_fprintf(2, "environment struct empty\n");
		return ;
	}
	while (current != NULL)
	{
		printf("%s\n", current->var);
		current = current->next;
	}
}
