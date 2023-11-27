/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:23:40 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/27 13:41:20 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_whitespaces(char *str, int i);
static char	*copy_quotes(char *str, char *output, int *i_str, int *i_output);
static void	print_output(char **split, char *output);

/// @brief Prints the input str
/// @param split the splitted string
/// @param str the whole string (needed for spaces)
/// @return 0 on succes, 1 on malloc fail
int	builtin_echo(char **split, char *str)
{
	char	*output;
	int		i_str;
	int		i_output;

	i_output = 0;
	if (split[1] == NULL)
		return (write(1, "\n", 1), 0);
	i_str = skip_whitespaces(str, 4);
	if (!ft_strncmp(str + i_str, "-n ", 3) || !ft_strncmp(str + i_str, "-n", 3))
		i_str = i_str + 3;
	output = ft_calloc(ft_strlen(str) + 2 - i_str, sizeof(char));
	if (output == NULL)
		return (ft_fprintf(2, "malloc fail in echo\n"), 1);
	while (str[i_str] != '\0')
	{
		i_str = skip_whitespaces(str, i_str);
		while (str[i_str] && !ft_isblank(str[i_str]) && !ft_isquote(str[i_str]))
			output[i_output++] = str[i_str++];
		if (str[i_str] && ft_isblank(str[i_str]) == 1)
			output[i_output++] = str[i_str++];
		if (str[i_str] != '\0' && ft_isquote(str[i_str]) != 0)
			output = copy_quotes(str, output, &i_str, &i_output);
	}
	print_output(split, output);
	return (free(output), 0);
}

/// @brief Copies the quoted sections of the str and if needed a space
/// @param str the str to copy from
/// @param output the destination
/// @param i_str the start position in the str
/// @param i_output start position in the destination
/// @return a pointer to the str
static char	*copy_quotes(char *str, char *output, int *i_str, int *i_output)
{
	char	type;

	type = str[*i_str];
	(*i_str)++;
	while (str[*i_str] != type)
	{
		output[*i_output] = str[*i_str];
		(*i_str)++;
		(*i_output)++;
	}
	(*i_str)++;
	if (str[*i_str] == ' ' || str[*i_str] == '\t')
	{
		output[*i_output] = str[*i_str];
		(*i_str)++;
		(*i_output)++;
	}
	*i_str = skip_whitespaces(str, *i_str);
	return (output);
}

/// @brief Skips the whitespaces
/// @param str the string to skip in
/// @param i the position in string
/// @throw isnt NULL protected
/// @return the first non whitespace position after i
static int	skip_whitespaces(char *str, int i)
{
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

static void	print_output(char **split, char *output)
{
	write(1, output, ft_strlen(output));
	if (ft_strncmp(split[1], "-n", 3) != 0)
		write(1, "\n", 1);
}
