/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:54:28 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/14 15:59:00 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
