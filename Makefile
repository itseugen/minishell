# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 13:58:27 by eweiberl          #+#    #+#              #
#    Updated: 2023/11/25 00:33:45 by adhaka           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LINKS = -lreadline
LINKS += -L./libft -lft
LINKS += -L./libmock -lmock

SOURCE = main.c
SOURCE += setup/get_prompt.c
SOURCE += execution/execute.c
SOURCE += builtins/env.c builtins/pwd.c builtins/cd.c builtins/is_builtin.c builtins/echo.c
SOURCE += builtins/unset.c builtins/export.c
SOURCE += operations/pipe.c
SOURCE += utils/ft_split_minishell.c utils/ft_is.c utils/rem_quotes.c
SOURCE += lexer/check_token.c lexer/lexer.c lexer/lexer_utils.c
SOURCE += expander/expander.c expander/expand_tokens.c
SOURCE += parser/parser.c parser/parser_utils.c parser/exec_cmds.c
SOURCE += environment/env_init.c environment/env_utils.c environment/env_operations.c
SOURCE += sig_hndlr/signal_main.c
SOURCE += environment/env_get_envp.c

LIBFT_GIT = https://github.com/itseugen/c_library
LIBFT_DIR = ./libft
LIBFT_LIB = libft.a
LIBFT	  = $(LIBFT_DIR)/$(LIBFT_LIB)

LIBMOCK_DIR = ./libmock
LIBMOCK_LIB = libmock.a
LIBMOCK = $(LIBMOCK_DIR)/$(LIBMOCK_LIB)

OBJS = $(SOURCE:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS) $(LIBMOCK)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJS) $(LINKS)

nflag: CFLAGS =
nflag: all

debug: CFLAGS += -g -arch x86_64
debug: re

$(LIBFT):
	git clone $(LIBFT_GIT) $(LIBFT_DIR); make -C $(LIBFT_DIR)

$(LIBMOCK):
	@cd $(LIBMOCK_DIR); make

libclean:
	rm -rf $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@cd libft && make clean
	@cd $(LIBMOCK_DIR) && make clean

fclean: clean
	@rm -f $(NAME)

re: fclean libclean all

.PHONY: re all clean nflag debug fclean libclean
