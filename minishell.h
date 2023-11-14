/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:13 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/14 17:36:25 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                Libraries                                   */
/* ************************************************************************** */

# include "libft/libft.h"
# include "libmock/mock_functions.h"

# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

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
	LIMITER,
	SEMICOLON
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

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */

int		execute_cmd(char **cmd, char **envp);

/* ************************************************************************** */
/*                                builtins                                    */
/* ************************************************************************** */

// bool	is_builtin(char *str);
int		execute_builtin(char *str, char *args, char **envp);
int		builtin_env(char **envp);
int		builtin_pwd(char **envp);
// int		builtin_cd(char *path);

int		builtin_cd(char **cmds);

/* ************************************************************************** */
/*                                  Lexer                                     */
/* ************************************************************************** */

void	free_tokens(t_token **token_list);
bool	is_redirect(char *cmd);
t_token	*tokenizer(char *input);
void	assign_id(t_token *token_list);
bool	is_builtin(char *cmd);

/* ************************************************************************** */
/*                                  Parser                                    */
/* ************************************************************************** */

int		parser(t_token *tokens, char **envp);
int		executor(t_token *tokens, char **envp);

/* ************************************************************************** */
/*                                  Expander                                  */
/* ************************************************************************** */

char	*expander(char *arg, char**envp);
int		expand_tokens(char **envp, t_token *tokens);

/* ************************************************************************** */
/*                                 Environment                                */
/* ************************************************************************** */
t_env	*env_init(char **envp);
void	free_env_struct(t_env **env_list);
int		env_size(t_env *env_list);
int		rem_env_var(char *name, t_env **env_list);
int		replace_env_var(char *name, char *value, t_env *env_list);

/* ************************************************************************** */
/*                                  Utils                                     */
/* ************************************************************************** */

char	*get_prompt(void);
char	**ft_split_minishell(char const *s, char c);
void	free_strings(void **strings);

/* ************************************************************************** */
/*                               test_fuctions                                */
/* ************************************************************************** */

/*
** functions needed for testing purposes, name should start with t_
*/
void	t_print_tokens(t_token *tokens);
void	t_print_env_struct(t_env *environment_list);

#endif