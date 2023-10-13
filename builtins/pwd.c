/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:35:08 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/13 14:01:07 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(char **envp)
{
	char	*pwd_str;

	pwd_str = NULL;
	(void)envp;
	// pwd_str = getenv("PWD");
	// if (pwd_str == NULL)
	// 	return (perror("pwd not found"), 1);
	// printf("%s\n", pwd_str);

	pwd_str = getcwd(NULL, 0);
	if (pwd_str == NULL)
		return (perror("pwd not found"), 1);
	printf("%s\n", pwd_str);
	free(pwd_str);
	return (0);
}
