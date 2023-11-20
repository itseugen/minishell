/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:35:08 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/20 13:53:01 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Prints the current working directory
/// @param env_list the environment list
/// @return 0 on success, 1 if PWD doesnt exist
int	builtin_pwd(t_env *env_list)
{
	char	*pwd_str;

	(void)env_list;
	pwd_str = getcwd(NULL, 0);
	if (pwd_str == NULL)
		return (ft_fprintf(2, "pwd: getcwd fail\n"), 1);
	printf("%s\n", pwd_str);
	free(pwd_str);
	return (0);
}
