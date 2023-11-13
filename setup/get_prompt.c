/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:36:47 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/13 14:30:07 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Returns the malloced prompt to display
/// @param  
/// @return Prompt is malloced and has to be freed
char	*get_prompt(void)
{
	char	*prompt;
	char	*username;

	username = getenv("USER");
	prompt = ft_strjoin(username, " % ");
	return (prompt);
}
