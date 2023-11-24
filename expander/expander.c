/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:47:20 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/24 22:37:47 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_var(char *input, int *old_i, t_env *env_list);
static int	skip_quotes(char *s, int i);
// static char	*expand_question_mark(char *input, int *old_i);

//* Variables can contain alphanumeric + _
//* Variables can't start with a number
//*

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
		// if (arg[i] == '$' && arg[i + 1] == '?')
		// {
		// 	i++;
		// 	arg = expand_question_mark(arg, &i);
		// 	if (arg == NULL)
		// 		return (ft_fprintf(2, "malloc fail in expander\n"), NULL);
		// 	while (ft_isalnum(arg[i]) != 0 || arg[i] == '_')
		// 		i++;
		// }
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
		i++;
	}
	return (arg);
}

// static char	*expand_question_mark(char *input, int *old_i)
// {
// 	int		i;
// 	char	*before_var;
// 	char	*after_var;
// 	char	*var_val;

// 	i = *old_i;
// 	*(old_i + 1);
// 	before_var = ft_substr(input, 0, i - 1);
// 	if (before_var == NULL)
// 		return (free(input), NULL);
// 	var_val = ft_itoa(get_exit_code());
// 	if (var_val == NULL)
// 		return (free(before_var), free(input), NULL);
// 	after_var = ft_strjoin(before_var, var_val);
// 	free(before_var);
// 	before_var = input;
// 	input = ft_strjoin(after_var, input + i + 1);
// 	return (free(after_var), free(before_var), free(var_val), input);
// }

static char	*expand_var(char *input, int *old_i, t_env *env_list)
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
