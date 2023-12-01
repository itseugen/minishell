/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:37:12 by adhaka            #+#    #+#             */
/*   Updated: 2023/12/01 06:50:34 by adhaka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (str[i] == '>' || str[i] == '<')
		i = 2;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	l = (char *)ft_calloc((word_len(str, i) + 1), sizeof(char));
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
		fd = open(str, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		return (ft_fprintf(2, "Error opening output file\n"), -1);
	return (fd);
}

int	handling(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp->prev)
	{
		if (tmp->prev->operation == REDIRECT)
			tmp = tmp->prev;
		else if (tmp->prev->operation == CMD)
		{
			tmp = tmp->prev;
			break ;
		}
	}
	if (tmp->operation == CMD && tmp->next != NULL)
	{
		if (red_maker(tokens, 0) == -1)
			return (-1);
	}
	else if (tmp->next != NULL)
	{
		if (red_maker(tokens, 1) == -1)
			return (-1);
	}
	return (0);
}

int	h_doc(t_token *tokens, t_env *env)
{
	int		i;
	int		j;
	char	*l;
	char	*str;

	i = 2;
	j = 0;
	str = ft_strdup(tokens->cmd);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	l = (char *)ft_calloc((word_len(str, i) + 1), sizeof(char));
	if (!l)
		return (-1);
	while (str[i] && !((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
	{
		l[j] = str[i];
		i++;
		j++;
	}
	l[j] = '\0';
	free(str);
	tokens->tmp = here_doc(env, l);
	return (0);
}

int	qcheck(t_token *tokens)
{
	int		i;
	t_token	*head;

	i = 0;
	head = tokens;
	while (head)
	{
		head = head->next;
		i++;
	}
	if (((tokens->operation != CMD)
			&& (tokens->operation != HERE_DOC)) && i == 1)
	{
		if (tokens->operation == REDIRECT)
		{
			if (tokens->cmd[0] == '<')
				ft_open(tokens->cmd, 0);
			else
				ft_open(tokens->cmd, 1);
		}
		return (-1);
	}
	return (0);
}
