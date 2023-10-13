/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/13 13:58:30 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*test;
	char	*prompt;

	(void)argc;
	(void)argv;
	prompt = get_prompt();
	test = readline(prompt);
	printf("%s\n", test);
	if (ft_strncmp(test, "env", 4) == 0)
		builtin_env(envp);
	else if (ft_strncmp(test, "pwd", 4) == 0)
		builtin_pwd(envp);
	else if (ft_strncmp(test, "cd ", 3) == 0)
	{
		builtin_cd("/Users/eweiberl/Docker");
		builtin_pwd(envp);
	}
	else
	{
		execute_cmd(ft_split(test, ' '), envp);
		free(prompt);
		free(test);
	}
	// system("leaks minishell");
	return (0);
}

/*
Display a prompt when waiting for a new command.
• Have a working history.
• Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
• Avoid using more than one global variable to indicate a received signal. Consider
the implications: this approach ensures that your signal handler will not access your
main data structures.1

! Not interpret unclosed quotes or special characters which are not required by the
! subject such as \ (backslash) or ; (semicolon).
• Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
• Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).

! • Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
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
! ◦ echo with option -n
! ◦ cd with only a relative or absolute path
* DONE ◦ pwd with no options
! ◦ export with no options
! ◦ unset with no options
* DONE ◦ env with no options or arguments
! ◦ exit with no options

*/