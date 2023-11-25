/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/25 01:11:13 by adhaka           ###   ########.fr       */
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
//! please dont work without fix token, complete documention would be written tommorow.

int	main(int argc, char **argv, char **envp)
{
	char	*test;
	char	*prompt;
	t_token	*tokens;
	t_env	*env_list;
	t_exec	**exec;
	int		i;

	signal(SIGINT, sig_type);
	signal(SIGQUIT, sig_type);
	clear_sigargs();
	// atexit(leaks);
	(void)argc;
	(void)argv;
	exec = NULL;
	i = 0;
	env_list = env_init(envp);
	while (1)
	{
		prompt = get_prompt();
		test = readline(prompt);
		// Split test or whatever its called with minishellsplit, tokenize, execute after
		if (test != NULL && test[0] != '\0')
			add_history(test);
		tokens = tokenizer(test);
		if (tokens == NULL)
			printf("Error\n");
		// t_print_tokens(tokens);
		fix_tokens(tokens);
		expand_tokens(env_list, tokens);
		// printf("Command after expand:\n");
		// t_print_tokens(tokens);
		if (mainpars(tokens) == -1)
			return (ft_fprintf(2, "parse error\n"), -1);
		exec = commands_for_exec(tokens);
		if (!exec)
			return (ft_fprintf(2, "Execution command initialization error\n"), -1);
		i = 0;
		// while (exec[i])
		// {
		// 	printf("%s------%d\n", exec[i]->cmds[0], exec[i]->in_fd);
		// 	i++;
		// }
		i = 0;
		if (tokens != NULL)
			free_tokens(&tokens);
		free(test);
		//! now call parser
		//! use ft_split_minishell2
		//! use rem_quotes after
		free(prompt);
	}
	free(prompt);
	free_env_struct(&env_list);
	system("leaks minishell");
	return (0);
}

/*
Display a prompt when waiting for a new command.
• Have a working history.
• Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
• Avoid using more than one global variable to indicate a received signal.
Consider the implications: this approach ensures that your signal handler
will not access your main data structures.1

! Not interpret unclosed quotes or special characters which are not required
!by the subject such as \ (backslash) or ; (semicolon).
* DONE • Handle ’ (single quote) which should prevent the shell from
* interpreting the meta-characters in the quoted sequence. interpreting
* DONE • Handle " (double quote) which should prevent the shell from
* the meta-characters in the quoted sequence except for $ (dollar sign).

! • Implement redirections:
! ◦ < should redirect input.
! ◦ > should redirect output.
! ◦ << should be given a delimiter, then read the input until a line containing
! the delimiter is seen. However, it doesn’t have to update the history!
! ◦ >> should redirect output in append mode.

! • Implement pipes (| character). The output of each command in the pipeline is
! connected to the input of the next command via a pipe.

* DONE • Handle environment variables ($ followed by a sequence of characters) which
* should expand to their values.

TODO: Change expander to handle it, use signal/global/getter function
! • Handle $? which should expand to the exit status of the most recently
! executed foreground pipeline.

TODO: Part of signal handling
! • Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
! ◦ ctrl-C displays a new prompt on a new line.
! ◦ ctrl-D exits the shell.
! ◦ ctrl-\ does nothing.

• Your shell must implement the following builtins:
* DONE ◦ echo with option -n
* DONE ◦ cd with only a relative or absolute path (Doesnt set PATH-Var)
* DONE ◦ pwd with no options
* DONE ◦ export with no options
* DONE ◦ unset with no options
* DONE ◦ env with no options or arguments
TODO: Same as ctrl-D -> handle together
! ◦ exit with no options

*/
