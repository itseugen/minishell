/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/10 16:48:56 by eweiberl         ###   ########.fr       */
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
	execute_cmd(ft_split(test, ' '), envp);
	free(prompt);
	free(test);
	// system("leaks minishell");
	return (0);
}
