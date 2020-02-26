# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpetrova <r11tsa@yahoo.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/26 20:38:13 by vpetrova          #+#    #+#              #
#    Updated: 2020/02/26 20:41:34 by vpetrova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS := -Wall -Werror -Wextra -O3
NAME := rushbsq
SRCS := rushbsq.c file.c file1.c map.c ftatoi.c
OBJS := $(patsubst %.c, %.o, $(SRCS))

all: $(NAME)

fclean:
	rm -f *.o $(NAME)

clean: fclean

re: fclean all

$(NAME): $(OBJS)

.PHONY = fclean clean all re


