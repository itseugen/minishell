/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:05:18 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/20 16:29:48 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_name(char *str);

int	builtin_unset(char **split, t_env *env_list)
{
	int	i;

	i = 1;
	if (split[0] == NULL || split[1] == NULL)
		return (1);
	while (split[i] != NULL)
	{
		if (check_name(split[1]) != 0
			|| get_env_var(split[1], env_list) == NULL)
		{
			i++;
			break ;
		}
		rem_env_var(split[1], env_list);
	}
	return (0);
}

/// @brief Checks if the variable name is valid
/// @param str 
/// @return 0 for correct input, 2 if theres nothing to do, 1 to give an error
static int	check_name(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (ft_fprintf(2, "'%s': Not a valid identifier\n", str), 1);
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (ft_fprintf(2, "'%s': Not a valid identifier\n", str), 1);
		i++;
	}
	return (0);
}
