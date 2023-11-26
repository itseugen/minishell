/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 04:13:05 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/26 22:20:08 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* We need to add a if for:
* TODO: Current is redirect and next is redirect
* TODO: All here_doc cases
* TODO: Make sure we dont leak any fds
! Advantages: We can easily implement ;
! Advantages: Might be slightly lighter and easier to modify to edge cases
! Disadvantages: Needs half a day of work to be on the state of your executor
*/

/*
* Calling: The parser gets called right after the lexer,
* This parser has the executor integrated for now, it might be moved
* into different functions if we choose to use it.
*/

///@brief Goes through the lexer and execute commands
int	parser(t_env *env_list, t_token *tokens)
{
	t_token	*current;
	int		pipe_fd[2]; 
	pid_t	pro_id;

	current = tokens;
	//opens all files, closes them if one fails ending the execution
	if (open_files(tokens) == 1)
		return (close_files(tokens), 1);
	while (current != NULL)
	{
		//skips the pipe operation from the lexer
		if (current->operation == PIPE)
			current = current->next;
		if (pipe(pipe_fd) == -1)
			return (perror("pipe fail"), 1);
		//executes the infile and the command after
		if (current->operation == INFILE)
		{
			pro_id = fork();
			if (pro_id == 0)
				first_child(pipe_fd, current, env_list);
			current = current->next;
		}
		//executes the cmd and the redirect after
		else if (current->operation == CMD && current->next != NULL && current->next->operation == REDIRECT)
		{
			pro_id = fork();
			if (pro_id == 0)
				last_child(pipe_fd, current, env_list);
			current = current->next;
		}
		else if (current->operation == CMD)
		{
			pro_id = fork();
			if (pro_id == 0)
				middle_child(pipe_fd, current, env_list);
		}
		close(pipe_fd[1]);
		//prints the pipe to the STDOUT if the last CMD isnt a redirect
		if (current->next == NULL && current->operation == CMD)
		{
			char	*gnl;
			gnl = get_next_line(pipe_fd[0]);
			while (gnl != NULL)
			{
				printf("%s", gnl);
				free(gnl);
				gnl = get_next_line(pipe_fd[0]);
			}
		}
		else if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (perror("dup2 fail"), 1);
		close(pipe_fd[0]);
		current = current->next;
	}
	return (close_files(tokens), 0);
}
