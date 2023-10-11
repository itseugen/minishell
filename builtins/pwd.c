/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:35:08 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/11 17:44:19 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(char **envp)
{
	char	*pwd_str;

	pwd_str = NULL;
	(void)envp;
	pwd_str = getenv("PWD");
	if (pwd_str == NULL)
		return (perror("pwd not found"), 1);
	printf("%s\n", pwd_str);
	return (0);
}
