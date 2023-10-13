/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:46:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/13 13:57:08 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char *path)
{
	int	ret;

	printf("%s\n", path);
	if (path == NULL)
		return (1);
	if (path[0] == '/')
	{
		ret = chdir(path);
		return (ret);
	}
	return (0);
}
