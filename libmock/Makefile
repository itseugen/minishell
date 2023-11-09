# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 20:43:10 by eweiberl          #+#    #+#              #
#    Updated: 2023/11/09 21:32:40 by eweiberl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmock.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCE = t_funcs.c

OBJS = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re