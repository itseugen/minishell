/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:57:07 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/14 17:37:44 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Replaces the value of a variable
/// @param name the name of the variable to replace
/// @param value the new value
/// @param env_list the list of variables
/// @return 0 on succes, 1 on malloc fail
int	replace_env_var(char *name, char *value, t_env *env_list)
{
	t_env	*current;
	size_t	name_len;

	name_len = ft_strlen(name);
	current = env_list;
	while (current != NULL)
	{
		if (ft_strncmp(name, current->var, name_len) == 0)
		{
			free(current->var);
			current->var = ft_strjoin(name, value);
			if (current->var == NULL)
				return (ft_fprintf(2, "Malloc fail in replace_env\n"), 1);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

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
