/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:31:06 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/16 15:47:53 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		count_substr(char const *s, char c);
static void		free_strings(void **strings, size_t size);
static int		skip_quotes(char const *s, int i);

/// @brief Split for minishell
/// @param s 
/// @param c just if needed, should always be space
/// @return array of split commands or NULL
char	**ft_split_minishell(char const *s, char c)
{
	int	substr_ctr;

	if (s == NULL)
		return (NULL);
	substr_ctr = count_substr(s, c);
	printf("Count: %d\n", substr_ctr);
	return (NULL);
}

/// @brief Counts substring and quotes
/// @param s 
/// @param c 
/// @return Amount of substr, -1 if quote is unfinished
static int	count_substr(char const *s, char c)
{
	int		i;
	size_t	ctr;

	i = 0;
	ctr = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			ctr++;
		if (s[i] != '\0' && (s[i] == '"' || s[i] == '\''))
			i = skip_quotes(s, i);
		while ((s[i + 1] == '\'' || s[i + 1] == '"') && i != -1 && ctr++)
			i = skip_quotes(s, i + 1);
		if (i == -1)
			return (-1); //!handle finishing the quote later (maybe call strjoin on this and the next line)
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (ctr);
}

static int	skip_quotes(char const *s, int i)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] != '"' && s[i] != '\0')
			i++;
	}
	else
	{
		i++;
		while (s[i] != '\'' && s[i] != '\0')
			i++;
	}
	if (s[i] == '\0')
		return (-1);
	return (i);
}

static void	free_strings(void **strings, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
