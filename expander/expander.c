/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:47:20 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/29 18:49:50 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_var(char *input, int *old_i, t_env *env_list);
static int	skip_quotes(char *s, int i);
static char	*expand_var_return(int i, t_env *env_list, char **split);
static char	*expand_question_mark(char *input, int *old_i);

//! Implement $? once signals are handled
//! Infrastructure for $? implemented, untested.
//! The function referenced by expand_question mark is just an idea ->
//! We either handle the exit code in the global (means no function necessary)
//! Or we use a getter?setter function with a static variable

/// @brief Expands all variables in the args
/// @param arg input to expand
/// @param envp finding the environent variables
/// @return
char	*expander(char *arg, t_env *env_list)
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
			arg = expand_var(arg, &i, env_list);
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
		if (arg[i] != '$')
			i++;
	}
	return (arg);
}

static char	*expand_question_mark(char *input, int *old_i)
{
	int		i;
	char	*before_var;
	char	*after_var;
	char	*var_val;

	i = *old_i;
	before_var = ft_substr(input, 0, i - 1);
	if (before_var == NULL)
		return (free(input), NULL);
	var_val = ft_itoa(0);
	if (var_val == NULL)
		return (free(before_var), free(input), NULL);
	after_var = ft_strjoin(before_var, var_val);
	free(before_var);
	before_var = input;
	input = ft_strjoin(after_var, input + i + 1);
	return (free(after_var), free(before_var), free(var_val), input);
}

static char	*expand_var(char *input, int *old_i, t_env *env_list)
{
	int		i;
	char	*b_var;
	char	var_name[256];
	int		start;
	char	*after_var;

	i = *old_i;
	if (input[i] == '?')
		return (expand_question_mark(input, old_i));
	if (input[i] != '_' && ft_isalnum(input[i]) == 0)
		return (input);
	b_var = ft_substr(input, 0, i - 1);
	if (ft_isdigit(input[i]) != 0)
	{
		after_var = ft_strjoin(b_var, input + i + 1);
		return (free(b_var), free(input), after_var);
	}
	if (b_var == NULL)
		return (free(input), NULL);
	start = i;
	while (input[i] != '\0' && (ft_isalnum(input[i]) != 0 || input[i] == '_'))
		i++;
	ft_strlcpy(var_name, input + start, i - start + 1);
	*old_i = i;
	return (expand_var_return(i, env_list, (char *[]){b_var, var_name, input}));
}

static char	*expand_var_return(int i, t_env *env_list, char **split)
{
	char	*before_var;
	char	*var_name;
	char	*input;
	char	*after_var;

	before_var = split[0];
	var_name = split[1];
	input = split[2];
	if (get_env_var(var_name, env_list) == NULL)
	{
		after_var = ft_strjoin(before_var, input + i);
		return (free(input), free(before_var), after_var);
	}
	else
	{
		after_var = ft_strjoin(before_var, get_env_var(var_name, env_list));
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
