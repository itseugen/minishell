/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:13 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/10 16:29:50 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                Libraries                                   */
/* ************************************************************************** */

# include "libft/libft.h"

# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ************************************************************************** */
/*                            Defines & enums                                 */
/* ************************************************************************** */

enum e_token
{
	EMPTY = 0,
	PIPE,
	HERE_DOC
};

/* ************************************************************************** */
/*                          Typedefs and globals                              */
/* ************************************************************************** */

typedef struct s_token
{
	char			*cmd;
	int				operation;
	struct s_token	*next;
}	t_token;

/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */

int		execute_cmd(char **cmd, char **envp);

/* ************************************************************************** */
/*                                  Utils                                     */
/* ************************************************************************** */

char	*get_prompt(void);

#endif