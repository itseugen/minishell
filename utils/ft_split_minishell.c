/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:31:06 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/21 18:43:08 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		count_substr(char const *s, char c);
static int		skip_quotes(char const *s, int i);
static char		*getstr(char const *s, int *old_i, char c);

/// @brief Split for minishell
/// @param s 
/// @param c just if needed, should always be space
/// @return array of split commands or NULL
char	**ft_split_minishell(char const *s, char c)
{
	int		substr_ctr;
	char	**strings;
	int		substr_fnd;
	int		i;

	i = 0;
	substr_fnd = 0;
	substr_ctr = count_substr(s, c);
	if (substr_ctr == -1)
		return (NULL);
	strings = (char **)ft_calloc(substr_ctr + 1, sizeof(char *));
	if (strings == NULL)
		return (NULL);
	while (substr_fnd < substr_ctr)
	{
		strings[substr_fnd] = getstr(s, &i, c);
		if (strings[substr_fnd] == NULL)
		{
			free_strings((void **)strings);
			return (NULL);
		}
		substr_fnd++;
	}
	return (strings);
}

static char	*getstr(char const *s, int *old_i, char c)
{
	int		start;
	char	*str;
	int		i;

	i = *old_i;
	while (s[i] == c && s[i] != '\0')
		i++;
	start = i;
	if (s[i] != '\0' && (s[i] == '"' || s[i] == '\''))
	{
		while (s[i] != '\0' && (s[i] == '"' || s[i] == '\''))
		{
			i = skip_quotes(s, i);
			i++;
			while (s[i] != '\0' && s[i] != c && s[i] != '"' && s[i] != '\'')
				i++;
		}
	}
	while (s[i] != c && s[i] != '\0')
		i++;
	str = ft_substr(s, start, (i - start));
	*old_i = i;
	return (str);
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
	if (s == NULL)
		return (-1);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			ctr++;
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] != '\0' && (s[i] == '"' || s[i] == '\''))
				i = skip_quotes(s, i);
			if (i == -1)
				return (-1);
			i++;
		}
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


void	free_strings(void **strings)
{
	size_t	i;

	i = 0;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
