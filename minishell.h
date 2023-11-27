/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:13 by eweiberl          #+#    #+#             */
/*   Updated: 2023/11/27 13:46:31 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                Libraries                                   */
/* ************************************************************************** */

# include "libft/libft.h"
# include "libmock/mock_functions.h"
// # include "pipex.h"

# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termios.h>
# include <errno.h>
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* ************************************************************************** */
/*                          Typedefs and globals                              */
/* ************************************************************************** */

typedef struct s_command
{
	int		in_fd;
	int		out_fd;
	char	*cmd_name;
	char	**cmd;
	char	*input_file;
	char	*output_file;
}	t_command;

typedef struct s_token
{
	char			*cmd;
	int				operation;
	t_command		*table;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_exec
{
	char				**cmds;
	int					in_fd;
	int					out_fd;
}	t_exec;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

void	executor(t_exec **exec, t_env *env);
char	**get_env(t_env *env);
char	**get_path(char	**envp);
char	*correct(t_exec *exec, char **envp);
void	ex(t_exec *exec, t_env *env, int tmp);
/* ************************************************************************** */
/*                                Executing                                   */
/* ************************************************************************** */

t_exec	**commands_for_exec(t_token *tokens);
int		execute_cmd(char **cmd, char **envp);
int		here_doc(t_env *env_list, int *pipe_fd, char **split);
void	fill(t_exec *exec, t_token *tokens);
int		cmd_counter(t_token *tokens);

/* ************************************************************************** */
/*                                builtins                                    */
/* ************************************************************************** */

int		execute_builtin(char *str, char *args, char **envp);
int		builtin_env(t_env *env_list);
int		builtin_pwd(t_env *env_list);
int		builtin_cd(char **cmds, t_env *env_list);
int		builtin_echo(char **split, char *str);
int		builtin_export(char **split, t_env *env_list);
int		builtin_unset(char **split, t_env *env_list);

/* ************************************************************************** */
/*                                  Lexer                                     */
/* ************************************************************************** */

void	free_tokens(t_token **token_list);
bool	is_redirect(char *cmd);
t_token	*tokenizer(char *input);
void	assign_id(t_token *token_list);
bool	is_builtin(char *cmd);
int		pipe_checker(char *tmp, int i);
void	fix_tokens(t_token *tokens);
int		lexer_redirects(int i, char *input);

/* ************************************************************************** */
/*                                  Parser                                    */
/* ************************************************************************** */

int		mainpars(t_token *tokens);
char	**my_split(char *str);
int		word_len(char *str, int i);
int		ft_open(char *str, int flag);
int		cmd_maker(t_token *tokens);
int		red_maker(t_token *tokens);
int		in_out(char *str, t_token *tmp, int flag);

/* ************************************************************************** */
/*                                  Expander                                  */
/* ************************************************************************** */

char	*expander(char *arg, t_env *env_list);
int		expand_tokens(t_env *env_list, t_token *tokens);

/* ************************************************************************** */
/*                                 Environment                                */
/* ************************************************************************** */

t_env	*env_init(char **envp);
void	free_env_struct(t_env **env_list);
int		env_size(t_env *env_list);
int		rem_env_var(char *name, t_env **env_list);
int		replace_env_var(char *name, char *value, t_env *env_list);
char	*get_env_var(char *name, t_env *env_list);
char	**env_get_envp(t_env *env_list);

/* ************************************************************************** */
/*                                  Utils                                     */
/* ************************************************************************** */

char	*get_prompt(void);
char	**ft_split_minishell(char const *s, char c);
void	free_strings(void **strings);
int		ft_isblank(char c);
int		ft_isquote(char c);
int		rem_quotes(char **split);

/* ************************************************************************** */
/*                                  Signals                                   */
/* ************************************************************************** */

void	ctrl_c(void);
void	ctrl_d(void);
void	ctrl_bs(void);
void	sig_type(int sig);
void	clear_sigargs(void);
int		mini_exit(t_token *tokens);
void	free_command(t_command *cmd);

/* ************************************************************************** */
/*                               test_fuctions                                */
/* ************************************************************************** */

/*
** functions needed for testing purposes, name should start with t_
*/
void	t_print_tokens(t_token *tokens);
void	t_print_env_struct(t_env *environment_list);

#endif
