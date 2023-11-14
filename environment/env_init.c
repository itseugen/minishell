/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:54:28 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/14 16:21:05 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Fills the env struct with all env strings
/// @param envp the NULL terminated array of env variables
/// @return returns an allocated struct with allocated vars inside
t_env	*env_init(char **envp)
{
	int		i;
	t_env	*env_list;
	t_env	*current;
	if (envp == NULL)
		return (NULL);
	i = 0;
	env_list = current;
	while (envp[i] != NULL)
	{
		current = ft_calloc(1, sizeof(t_env));
		if (current == NULL)
			return (free_env_struct(&env_list), NULL);
		current->next = NULL;
		current->var = ft_strdup(envp[i]);
		if (current->var == NULL)
			return (free_env_struct(&env_list), NULL);
		current = current->next;
		i++;
	}
	return (env_list);
}
