/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:10 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/09 18:41:11 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*test;
	char	*prompt;

	(void)argc;
	(void)argv;
	(void)envp;
	prompt = get_prompt();
	test = readline(prompt);
	printf("%s\n", test);
	free(prompt);
	free(test);
	// system("leaks minishell");
	return (0);
}
