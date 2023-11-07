/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:47:20 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/07 20:23:10 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_var(char *input, int *old_i);
static int	skip_quotes(char *s, int i);

//* Variables can contain alphanumeric + _
//* Variables can't start with a number
//*

/// @brief Expands all variables in the args
/// @param arg input to expand
/// @param envp finding the environent variables
/// @return 
char	*expander(char *arg, char**envp)
{
	int		i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (arg[i] != '\0')
	{
		if (ft_strchr(arg, '$') == NULL)
			return (arg);
		if (arg[i] == '$')
		{
			i++;
			arg = expand_var(arg, &i);
			if (arg == NULL)
				return (ft_fprintf(2, "malloc fail in expander\n"), NULL);
			while (ft_isalnum(arg[i]) != 0 || arg[i] == '_')
				i++;
		}
		else if (arg[i] == '"')
		{
			if (in_quotes == false)
				in_quotes = true;
			else
				in_quotes = false;
		}
		else if (arg[i] == '\'' && in_quotes == false)
			i = skip_quotes(arg, i);
		if (i == -1)
			return (ft_fprintf(2, "malloc fail in expander\n"), NULL);
		i++;
	}
	return (arg);
}

static char	*expand_var(char *input, int *old_i)
{
	int		i;
	char	*before_var;
	char	var_name[256];
	int		start;
	char	*after_var;

	i = *old_i;
	if (input[i] != '_' && ft_isalnum(input[i]) == 0)
		return (input);
	before_var = ft_substr(input, 0, i - 1);
	if (ft_isdigit(input[i]) != 0)
	{
		after_var = ft_strjoin(before_var, input + i + 1);
		return (free(before_var), free(input), after_var);
	}
	if (before_var == NULL)
		return (free(input), NULL);
	start = i;
	while (input[i] != '\0' && (ft_isalnum(input[i]) != 0 || input[i] == '_'))
		i++;
	ft_strlcpy(var_name, input + start, i - start + 1);
	*old_i = i;
	if (getenv(var_name) == NULL)
	{
		after_var = ft_strjoin(before_var, input + i);
		return (free(input), free(before_var), after_var);
	}
	else
	{
		after_var = ft_strjoin(before_var, getenv(var_name));
		free(before_var);
		before_var = input;
		input = ft_strjoin(after_var, input + i);
		return (free(after_var), free(before_var), input);
	}
}

static int	skip_quotes(char *s, int i)
{
	i++;
	while (s[i] != '\'' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (-1);
	return (i);
}
