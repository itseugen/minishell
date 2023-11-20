/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/20 16:49:05 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* TODO:
* - Parser
* - executing
* - missing builtins
* - Syntax tree / command table
* - Signals
* - ctrl inputs
*/

/*
!Idea: Pass a pointer to the string returned by readline instead of using split
/*
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

int	main(int argc, char **argv, char **envp)
{
	char	*test;
	char	*prompt;
	t_token	*tokens;
	char	**split;
	t_env	*env_list;

	(void)argc;
	(void)argv;
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
		assign_id(tokens);
		expand_tokens(envp, tokens);
		// printf("Command after expand:\n");
		// t_print_tokens(tokens);
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
	// system("leaks minishell");
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
• Handle ’ (single quote) which should prevent the shell from
interpreting the meta-characters in the quoted sequence.
• Handle " (double quote) which should prevent the shell from interpreting
the meta-characters in the quoted sequence except for $ (dollar sign).

! • Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing
the delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.

! • Implement pipes (| character). The output of each command in the pipeline is
! connected to the input of the next command via a pipe.

! • Handle environment variables ($ followed by a sequence of characters) which
! should expand to their values.

! • Handle $? which should expand to the exit status of the most recently
! executed foreground pipeline.

! • Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
! ◦ ctrl-C displays a new prompt on a new line.
! ◦ ctrl-D exits the shell.
! ◦ ctrl-\ does nothing.

• Your shell must implement the following builtins:
* DONE ◦ echo with option -n
* DONE ◦ cd with only a relative or absolute path (Doesnt set PATH-Var)
* DONE ◦ pwd with no options
! ◦ export with no options
! ◦ unset with no options
TODO: GO through env and bzero the string equaling the var
* DONE ◦ env with no options or arguments
! ◦ exit with no options

*/
