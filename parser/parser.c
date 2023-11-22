/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 04:13:05 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/22 14:26:44 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* The parser:
* 1.	check for wrong pipes etc (I could also make a lexer expansion)
*		to take care of such errors
*
* 2.	open files -> if one open fails, do nothing and return to main
*
* 3.	initialise a command table if needed (if not we can just use the t_token)
*
* 4.	the parser/executor should also
*		- let the executor know what to pipe and what not to pipe
*		- When to redirect and when not
*		- have a clean structure the executor can use
*/

//! Why make arguments a list if every function need char **?
typedef struct s_argument
{
	char				*arg;
	struct s_argument	*next;
}	t_argument;

typedef struct s_command
{
	char				*cmd_name;			// Command or executable name
	t_argument			*args;		// List of command arguments
	char				*input_file;		// Input file for redirection (NULL if not used)
	char				*output_file;		// Output file for redirection (NULL if not used)
	int					append_output;		// Flag indicating whether to append to output file
	struct s_command	*next; // Pointer to the next command in a pipeline
}	t_command;

// Function to parse the token list and build a command table
int	parse_tokens(t_env *env_list, t_token *tokens)
{
	t_command	*command_table;
	t_command	*current_command;
	t_token		*current_token;

	if (!tokens)
		return (1);
	command_table = NULL;
	current_command = NULL;
	current_token = tokens;
	while (current_token)
	{
		if (handle_token(env_list, current_token, &current_command) != 0)
		{
			free_command_table(command_table);
			return (1);
		}
		current_token = current_token->next;
	}
	return (0);
}

static int	handle_token(t_env *env_list, t_token *current_token, t_command **current_command)
{
	t_command	*next_command;

	//! Why not just check for == CMD since BUILTIN doesnt exist yet and ARGUMENT is a part of CMD
	if (current_token->operation == CMD || current_token->operation == BUILTIN || current_token->operation == ARGUMENT)
	{
		//! Why expand here -> using expand before parser saves lines
		current_token->cmd = expander(current_token->cmd, env_list);
		if (!current_token->cmd)
			return (1);
		if (*current_command == NULL)
			*current_command = create_command(current_token->cmd);
		//! Why do the arguments here? More allocation out of scope -> more memmory management -> splitting the command into arguments before execve/builtins saves lots of memory management
		else
			add_argument(*current_command, current_token->cmd);
	}
	else if (current_token->operation == PIPE)
		return (handle_pipe_token(current_command));
		//! Not even a function -> handle redirection meant???
	else if (current_token->operation == REDIRECT)
		return (handle_redirect_token(env_list, current_token, current_command));
	//! what does this function even do? If we choose to implement semicolons -> create a second command table / call parser with other half of lexer after executing before semicolon
	else if (current_token->operation == SEMICOLON)
		return (handle_semicolon_token(current_command));
	return (0);
	}

static int	handle_redirection(t_env *env_list, t_token *current_token, t_command *current_command)
{
	//! lexer puts redirect and file name / limiter in one string -> why not handle it via this instead of recoding the lexer
	if (!current_token->next || (current_token->next->operation != CMD && current_token->next->operation != ARGUMENT))
		return (1);
	//! Again why not just expand before parser
	current_token->next->cmd = expander(current_token->next->cmd, env_list);
	if (!current_token->next->cmd)
		return (1);
	//! is it good to handle the logic here instead of later? if so, what should this function handle?
	//! Should it do opens or dup2 (wouldnt work since there might be redirects before it)
	//! Might make sense if function only handles open since open fail->dont do anything else
	if (handle_redirection_logic(current_token->operation, current_token->next->cmd, &current_command) != 0)
		return (1);
	return (0);
}

static int	handle_pipe_token(t_command **current_command)
{
	t_command	*next_command;

	if (*current_command == NULL)
		return (1);
	next_command = create_command(NULL);
	(*current_command)->next = next_command;
	*current_command = next_command;

	return (0);
}

static int	handle_semicolon_token(t_command **current_command)
{
	if (*current_command != NULL)
	{
		*current_command = NULL;
	}
	return (0);
}

// Function to free the command table
//! Doesnt free input/output strings
//! also if you want to comment functions use @brief instead of normal comments
void	free_command_table(t_command *command_table)
{
	t_command	*current;
	t_command	*next;

	current = command_table;
	while (current != NULL)
	{
		next = current->next;
		free_arguments(current->args);
		free(current);
		current = next;
	}
}

// Function to create a new command with a given command name
t_command	*create_command(char *cmd_name)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd_name = cmd_name;
	command->args = NULL;
	command->input_file = NULL;
	command->output_file = NULL;
	command->next = NULL;
	return (command);
}

// Function to add an argument to a command
void	add_argument(t_command *command, char *arg)
{
	t_argument	*argument;
	t_argument	*current;

	argument = malloc(sizeof(t_argument));
	if (!argument)
		return (NULL);
	argument->arg = arg;
	argument->next = NULL;
	if (command->args == NULL)
	{
		command->args = argument;
	}
	else
	{
		current = command->args;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = argument;
	}
}

// Function to free the arguments of a command
void	free_arguments(t_argument *args)
{
	t_argument	*next;
	t_argument	*current;

	current = args;
	while (current != NULL)
	{
		next = current->next;
		free(current->arg);
		free(current);
		current = next;
	}
}
// Function to execute the command table
void execute_command_table(t_command *command_table)
{
	// TODO: Implement command execution logic
	// Traverse the command table and execute each command
	// may need to create processes, handle pipes, and set up file descriptors for redirection
}
