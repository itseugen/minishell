/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 03:27:50 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/23 11:06:56 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_len(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] && !((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
	{
		j++;
		i++;
	}
	return (j);
}

static int	word_counter(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		if (str[i])
			words++;
		while (str[i] && !((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			i++;
	}
	return (words);
}

static int	maker(char *str, int i, char **tmp, int x)
{
	int	j;

	j = 0;
	tmp[x] = (char *)malloc(sizeof(char) * (word_len(str, i) + 1));
	if (!tmp[x])
		free_strings((void **)tmp);
	while (str[i] && !((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
	{
		tmp[x][j] = str[i];
		i++;
		j++;
	}
	tmp[x][j] = '\0';
	return (i);
}

//! Again why this split? Whats the reasoning behind it?
//Answer: This is used when there are mixed spaces and tabs is the string for example "			ls -l 		 | wc >" which was complicated to handle with your split, so just wrote it as a util.
char	**my_split(char *str)
{
	int		i;
	char	**tmp;
	int		n_words;
	int		x;

	n_words = word_counter(str);
	i = 0;
	x = 0;
	tmp = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		if (str[i])
		{
			i = maker(str, i, tmp, x);
			x++;
		}
	}
	tmp[x] = NULL;
	return (tmp);
}
