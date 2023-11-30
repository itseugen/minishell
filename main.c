/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/29 19:56:01 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_last_exit_status = 0;
static int		setup(int argc, char **argv, t_env *env_list);
static t_token	*get_and_tokenize(t_env *env_list);

int	main(int argc, char **argv, char **envp)
{
	t_token	*tokens;
	t_env	*env_list;
	t_exec	**exec;

	env_list = env_init(envp);
	if (setup(argc, argv, env_list) == 1)
		exit(1);
	while (1)
	{
		tokens = get_and_tokenize(env_list);
		if (tokens == NULL)
			continue ;
		if (mainpars(tokens) == -1)
		{
			ft_fprintf(2, "parse error\n");
			continue ;
		}
		exec = commands_for_exec(tokens);
		free_tokens(&tokens);
		if (!exec)
			return (ft_fprintf(2, "command initialization error\n"), -1);
		executor(exec, env_list);
		free_exec_array(exec);
	}
	return (clear_history(), free_env_struct(&env_list), 0);
}

/// @brief Sets the signals, checks the env_list
/// @param argc 
/// @param argv 
/// @param env_list the list to check
/// @return 1 if the env_init failed, otherwise 0
static int	setup(int argc, char **argv, t_env *env_list)
{
	signal(SIGINT, sig_type);
	signal(SIGQUIT, sig_type);
	clear_sigargs();
	(void)argc;
	(void)argv;
	if (env_list == NULL)
	{
		ft_fprintf(2, "setup: setting up env failed\n", 1);
		return (1);
	}
	return (0);
}

/// @brief Gives the prompt, tokenizes the line, expands
/// @param env_list the env_list to expand variables
/// @return the tokens, NULL on Error/malloc fail
static t_token	*get_and_tokenize(t_env *env_list)
{
	char	*line;
	t_token	*tokens;
	char	*prompt;

	prompt = get_prompt();
	if (prompt == NULL)
		return (ft_fprintf(2, "prompt: malloc fail\n"), NULL);
	line = readline(prompt);
	if (line == NULL)
	{
		free_env_struct(&env_list);
		exit(0);
	}
	if (line[0] == '\0')
		return (NULL);
	add_history(line);
	tokens = tokenizer(line);
	if (tokens == NULL)
		return (free(line), ft_fprintf(2, "Error in tokenizer\n"), NULL);
	if (tokens->cmd[0] == '\0')
		return (free(line), free_tokens(&tokens), NULL);
	fix_tokens(tokens);
	if (expand_tokens(env_list, tokens) == 1)
		return (free(line), free_tokens(&tokens), NULL);
	return (tokens);
}
