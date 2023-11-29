/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 04:13:05 by adhaka            #+#    #+#             */
/*   Updated: 2023/11/29 14:19:52 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
*	The parser:
* 1.	check for wrong pipes etc (I could also make a lexer expansion)
*		to take care of such errors (done) -> (files in lexer_utils.c)
*
* 2.	open files -> if one open fails, do nothing and return to main (done)
*
* 3.	initialise a command table if needed (if not we can just use the t_token) (done)
*
* 4.	the parser/executor should also
*		- let the executor know what to pipe and what not to pipe ( not done( please explain a bit more))
*		- When to redirect and when not (done)
*		- have a clean structure the executor can use (done)
*/

/// @brief This is the main parser function that iterates
/// through the token list and calls specific functions
/// based on the type of operation in each token
/// @param tokens
/// @return 0
int	mainpars(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	while (head)
	{
		if (head->operation == CMD)
		{
			if (cmd_maker(head) == -1)
				return (-1);
		}
		else if (head->operation == REDIRECT)
		{
			if (red_maker(head) == -1)
				return (-1);
		}
		head = head->next;
	}
	return (0);
}

/// @brief Creates a command structure (t_command)
/// and populates it with information from the CMD token.
/// @param tokens
/// @return 0
int	cmd_maker(t_token *tokens)
{
	t_command	*tab;

	tab = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!tab)
		return (-1);
	// tab->cmd = my_split(tokens->cmd);
	tab->cmd = ft_split_minishell(tokens->cmd, ' ');
	rem_quotes(tab->cmd);
	if (tab->cmd == NULL)
		return (1);
	tab->cmd_name = ft_strdup(tab->cmd[0]);
	tab->in_fd = STDIN;
	tab->out_fd = STDOUT;
	tokens->table = tab;
	return (0);
}

/// @brief Handles redirection tokens and
///sets up the input and output file descriptors for a command.
/// @param tokens
/// @return
int	red_maker(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		tmp = tmp->prev;
		if (tmp && tmp->operation == CMD)
			break;
	}
	if (!tmp)
		return (-1);
	if (tokens->cmd[0] == '<')
	{
		if (in_out(tokens->cmd, tmp, 0) == -1)
			return (-1);
		tmp->table->in_fd = ft_open(tmp->table->input_file, 0);
		if (tmp->table->in_fd == -1)
			return (-1);
	}
	if (tokens->cmd[0] == '>')
	{
		if (in_out(tokens->cmd, tmp, 1) == -1)
			return (-1);
		if (tokens->cmd[1] == '>')
			tmp->table->out_fd = ft_open(tmp->table->output_file, 2);
		else
			tmp->table->out_fd = ft_open(tmp->table->output_file, 1);
		if (tmp->table->out_fd == -1)
			return (-1);
	}
	return (0);
}

/// @brief Extracts the input or output file name from the redirection token.
/// @param str
/// @param tmp
/// @param flag
/// @return 0
int	in_out(char *str, t_token *tmp, int flag)
{
	int		i;
	int		j;
	char	*l;

	i = 1;
	j = 0;
	if (str[i] == '>')
		i = 2;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	l = (char *)malloc(sizeof(char) * (word_len(str, i) + 1));
	if (!l)
		return (-1);
	while (str[i] && !((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
	{
		l[j] = str[i];
		i++;
		j++;
	}
	l[j] = '\0';
	if (!flag)
		tmp->table->input_file = l;
	else
		tmp->table->output_file = l;
	return (0);
}

/// @brief Opens a file with specific flags based on the provided parameters.
/// @param str
/// @param flag
/// @return fd
int	ft_open(char *str, int flag)
{
	int	fd;

	if (flag == 0)
	{
		if (access(str, F_OK) == 0 && access(str, R_OK) == 0)
		{
			fd = open(str, O_RDONLY);
			if (fd < 0)
				return (ft_fprintf(2, "Error opening input file\n"), -1);
		}
		else
			return (ft_fprintf(2, "Wrong input file\n"), -1);
	}
	if (flag == 1)
		fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (flag == 2)
		fd = open(str, O_APPEND | O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_fprintf(2, "Error opening output file\n"), -1);
	return (fd);
}
