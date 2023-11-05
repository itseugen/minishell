/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:13 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/05 14:05:40 by eweiberl         ###   ########.fr       */
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
# include <fcntl.h>

/* ************************************************************************** */
/*                            Defines & enums                                 */
/* ************************************************************************** */

enum e_token
{
	CMD = 0,
	BUILTIN,
	ARGUMENT,
	CONTENT,
	REDIRECT,
	PIPE,
	FD,
	HERE_DOC,
	LIMITER
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
	int				operation;
	struct s_token	*next;
	struct s_token	*prev;
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
/*                                  Lexer                                     */
/* ************************************************************************** */

t_token	*get_tokens(char **split);
void	free_tokens(t_token **token_list);
bool	is_redirect(char *cmd);

t_token	*tokenizer(char *input);

/* ************************************************************************** */
/*                                  Utils                                     */
/* ************************************************************************** */

char	*get_prompt(void);
char	**ft_split_minishell(char const *s, char c);
void	free_strings(void **strings);

#endif