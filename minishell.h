/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:13 by eweiberl          #+#    #+#             */
/*   Updated: 2023/10/17 16:33:42 by eweiberl         ###   ########.fr       */
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
	HERE_DOC,
	OPEN_FILE
};

/* ************************************************************************** */
/*                          Typedefs and globals                              */
/* ************************************************************************** */

/// Example:
/// Cmd = "<"
/// Args = token->next
/// operation = OPEN
/// next = "wc";
typedef struct s_token
{
	char			*cmd;
	char			**args;
	int				operation;
	struct s_token	*next;
}	t_token;

/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */

int		execute_cmd(char **cmd, char **envp);

/* ************************************************************************** */
/*                                builtins                                    */
/* ************************************************************************** */

bool	is_builtin(char *str);
int		execute_builtin(char *str, char *args, char **envp);
int		builtin_env(char **envp);
int		builtin_pwd(char **envp);
int		builtin_cd(char *path);

/* ************************************************************************** */
/*                                  Utils                                     */
/* ************************************************************************** */

char	*get_prompt(void);
char	**ft_split_minishell(char const *s, char c);

#endif