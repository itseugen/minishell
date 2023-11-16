/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:44:36 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/16 13:50:26 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Returns a envp like char**
/// @param env_list the environment list
/// @throw Only free the array NOT the content
/// @return returns the array or NULL on malloc fail
char	**env_get_envp(t_env *env_list)
{
	char	**ret;
	t_env	*current;
	int		i;

	i = 0;
	current = env_list;
	ret = ft_calloc(env_size(env_list) + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (current != NULL)
	{
		ret[i] = current->var;
		i++;
		current = current->next;
	}
	return (ret);
}
