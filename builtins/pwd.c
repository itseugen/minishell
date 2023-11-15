/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:35:08 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/15 15:47:08 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_env *env_list)
{
	char	*pwd_str;

	pwd_str = get_env_var("PWD", env_list);
	if (pwd_str == NULL)
		return (ft_fprintf(2, "pwd not found\n"), 1);
	printf("%s\n", pwd_str);
	return (0);
}
