# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 14:39:30 by mbankhar          #+#    #+#              #
#    Updated: 2024/05/29 13:01:21 by mbankhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# CFLAGS = -Wall -Wextra -Werror

SRCS = philo.c pars_and_error.c philo_utils.c

OBJS = $(SRCS:.c=.o)

NAME = philo

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	cc $(CFLAGS) -I$(HEADER) $(OBJS) -o $@
	
clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
















