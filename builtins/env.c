/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:23:40 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/15 15:50:04 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	if (current == NULL)
		return (ft_fprintf(2, "env list empty\n"), 1);
	while (current != NULL)
	{
		printf("%s\n", current->var);
		current = current->next;
	}
	return (0);
}
