/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/29 17:29:13 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* TODO:
* - Parser - done
* - executing
* - missing builtins
* - Syntax tree / command table
* - Signals
* - ctrl inputs
*/

/*
!Idea: Pass a pointer to the string returned by readline instead of using split
**
** char **cmd_table[]
** each index represents a command, the space between means to pipe
** we use minishell split to split the command, we can then
** check for </>/>> to pipe to file
**
*/

/*
** For the expander:
** IDEA: It take a string, checks for expandable variables
** if it finds any it expands them,
** frees the old string and returns a new one with the expanded variable
** else it just returns the old string
*/

// void	leaks()
// {
// 	system("leaks minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_env	*env_list;
	t_exec	**exec;

	signal(SIGINT, sig_type);
	signal(SIGQUIT, sig_type);
	clear_sigargs();
	(void)argc;
	(void)argv;
	exec = NULL;
	env_list = env_init(envp);
	while (1)
	{
		line = readline("minish % ");
		if (line == NULL) //Controll + D;
			break ;
		if (line[0] == '\0')
			continue ;
		add_history(line);
		tokens = tokenizer(line);
		free(line);
		if (tokens == NULL)
		{
			ft_fprintf(2, "Error in tokenizer\n");
			continue ;
		}
		if (tokens->cmd[0] == '\0')
		{
			free_tokens(&tokens);
			continue ;
		}
		fix_tokens(tokens);
		expand_tokens(env_list, tokens);
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
	}
	clear_history();
	free_env_struct(&env_list);
	return (0);
}
