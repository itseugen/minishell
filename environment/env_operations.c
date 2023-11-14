/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:57:07 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/14 17:13:01 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief removes an element from the env list
/// @param name the name of the variable to remove
/// @param env_list the list to remove from
/// @return 0 on succesfull remove, 1 on element not found
int	rem_env_var(char *name, t_env **env_list)
{
	t_env	*current;
	t_env	*free_me;
	size_t	name_len;

	name_len = ft_strlen(name);
	if (ft_strncmp(name, current->var, name_len) == 0)
	{
		*env_list = current->next;
		free(current->var);
		free(current);
		return (0);
	}
	while (current->next != NULL)
	{
		if (ft_strncmp(name, current->next->var, name_len) == 0)
		{
			free_me = current->next;
			current->next = free_me->next;
			free(free_me->var);
			free(free_me);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
