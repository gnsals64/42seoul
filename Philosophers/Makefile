# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 16:54:20 by hunpark           #+#    #+#              #
#    Updated: 2023/04/30 01:59:16 by hunpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAG = -g -Wall -Werror -Wextra -fsanitize=thread -g3
SRC_FILE = $(addprefix src/, main utils init thread_utils dine monitor)
SRCS = ${SRC_FILE:=.c}

all : ${NAME}

${NAME} :
	@${CC} ${FLAG} ${SRCS} -lpthread -o ${NAME}

clean :

fclean :
	@rm -f ${NAME}

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re
