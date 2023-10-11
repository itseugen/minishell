/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:35:08 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/11 17:40:40 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(char **envp)
{
	int		i;
	char	*pwd_str;

	i = 0;
	pwd_str = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			pwd_str = envp[i] + 4;
			break ;
		}
		i++;
	}
	if (pwd_str == NULL)
		return (perror("pwd not found"), 1);
	printf("%s\n", pwd_str);
	return (0);
}
