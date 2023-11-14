/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:54:28 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/14 16:45:44 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*add_first(char **envp);

/// @brief Fills the env struct with all env strings
/// @param envp the NULL terminated array of env variables
/// @return returns an allocated struct with allocated vars inside
t_env	*env_init(char **envp)
{
	int		i;
	t_env	*env_list;
	t_env	*current;
	if (envp == NULL || envp[0] == NULL)
		return (NULL);
	i = 1;
	env_list = add_first(envp);
	if (env_list == NULL)
		return (NULL);
	current = env_list;
	while (envp[i] != NULL)
	{
		current->next = ft_calloc(1, sizeof(t_env));
		if (current->next == NULL)
			return (free_env_struct(&env_list), NULL);
		current = current->next;
		current->next = NULL;
		current->var = ft_strdup(envp[i]);
		if (current->var == NULL)
			return (free_env_struct(&env_list), NULL);
		i++;
	}
	return (env_list);
}

static t_env	*add_first(char **envp)
{
	t_env	*env_list;

	env_list = ft_calloc(1, sizeof(t_env));
	if (env_list == NULL)
		return (NULL);
	env_list->next = NULL;
	env_list->var = ft_strdup(envp[0]);
	if (env_list->var == NULL)
		return (free(env_list), NULL);
	return (env_list);
}
