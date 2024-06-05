# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 14:39:30 by mbankhar          #+#    #+#              #
#    Updated: 2024/06/05 19:13:16 by mbankhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -g -Wall -Wextra -Werror

SRCS = philo.c pars_and_error.c philo_utils.c init.c routines.c

OBJS = $(SRCS:.c=.o)

NAME = philo

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	cc $(CFLAGS) -I$(HEADER) $(OBJS) -o $@ -pthread
	
clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
















