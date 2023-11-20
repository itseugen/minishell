/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 04:13:05 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/20 11:20:19 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Structure to represent a command
typedef struct s_command
{
	char				*cmd;
	char				*args[100];
	char				*input;
	char				*output;
	bool				append;
	char				*heredoc;
	struct s_command	*pipe;
}	t_command;

// Function to free memory allocated for a command
void	free_command(t_command *cmd)
{
	int	i;

	i = 0;
	free(cmd->cmd);
	while (cmd->args[i] != NULL)
	{
		free(cmd->args[i]);
		i++;
	}

	free(cmd->input);
	free(cmd->output);
	free(cmd->heredoc);
	free(cmd);
}

// Function to parse a command
t_command	*parse_command(char *command)
{
	t_command	*cmd;
	char		*token;
	int			arg_count;

	cmd = (t_command *)malloc(sizeof(t_command));
	cmd->cmd = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->append = false;
	cmd->heredoc = NULL;
	cmd->pipe = NULL;

	token = strtok(command, " ");
	arg_count = 0;

	while (token != NULL)
	{
		if (strcmp(token, "|") == 0)
		{
			// Handle pipes
			cmd->pipe = parse_command(NULL);
			break;
		}
		else if (strcmp(token, ">") == 0)
		{
			// Handle output redirection
			cmd->output = strdup(strtok(NULL, " "));
		}
		else if (strcmp(token, ">>") == 0)
		{
			// Handle append output redirection
			cmd->output = strdup(strtok(NULL, " "));
			cmd->append = true;
		}
		else if (strcmp(token, "<") == 0)
		{
			// Handle input redirection
			cmd->input = strdup(strtok(NULL, " "));
		}
		else if (strcmp(token, "<<") == 0)
		{
			// Handle heredoc
			cmd->heredoc = strdup(strtok(NULL, " "));
		}
		else
		{
			// Handle command and arguments
			if (cmd->cmd == NULL)
			{
				cmd->cmd = strdup(token);
			}
			else
			{
				cmd->args[arg_count++] = strdup(token);
				cmd->args[arg_count] = NULL;
			}
		}

		token = strtok(NULL, " ");
	}

	return (cmd);
}

// Function to free the memory of the entire command chain
void	free_commandchain(t_command *cmd)
{
	if (cmd == NULL)
	{
		exit(1);
	}
	free_commandchain(cmd->pipe);
	free_command(cmd);
}

// Function to print a command and its arguments
void	print_command(t_command *cmd)
{
	int	i;

	i = 0;
	printf("Command: %s\n", cmd->cmd);
	printf("Arguments: ");
	while (cmd->args[i] != NULL)
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	printf("\n");
	printf("Input: %s\n", cmd->input);
	printf("Output: %s\n", cmd->output);
	if (cmd->append)
	{
		printf("Append: true\n");
	}
	else
	{
		printf("Append: false\n");
	}
	printf("Heredoc: %s\n", cmd->heredoc);
	printf("\n");
}

int	main(void)
{
	char command[] = "ls -l < input.txt | grep py > output.txt";
	t_command *cmd = parse_command(command);
	print_command(cmd);
	free_commandchain(cmd);

	return (0);
}
