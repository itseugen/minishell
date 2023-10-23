/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:46:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/23 15:03:24 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char *path)
{
	int		ret;
	char	*home_dir;

	if (path == NULL || path[0] == '\0' || ft_strncmp(path, "~", 2) == 0)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
			return (perror("HOME variable not set"), 1);
		ret = chdir(home_dir);
	}
	else
		ret = chdir(path);
	return (ret);
}
