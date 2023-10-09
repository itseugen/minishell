# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 13:58:27 by eweiberl          #+#    #+#              #
#    Updated: 2023/10/09 16:33:05 by eweiberl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LINKS = -lreadline

SOURCE = main.c

LIBFT_GIT = https://github.com/itseugen/c_library
LIBFT_DIR = ./libft
LIBFT_LIB = libft.a
LIBFT	  = $(LIBFT_DIR)/$(LIBFT_LIB)

OBJS = $(SOURCE:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJS) $(LINKS)

dataraces: CFLAGS += -fsanitize=thread
dataraces: re

nflag: CFLAGS =
nflag: re

debug: CFLAGS += -g -arch x86_64
debug: re

$(LIBFT):
	git clone $(LIBFT_GIT) $(LIBFT_DIR); make -C $(LIBFT_DIR)

libclean:
	rm -rf $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@cd libft && make clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re all clean