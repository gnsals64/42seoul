# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 21:34:18 by hunpark           #+#    #+#              #
#    Updated: 2023/01/26 21:34:18 by hunpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
FLAG = -Wall -Werror -Wextra
SRCS = ./src/pipex.c \
		./src/utils.c \

LIBFT = ./libft

all : ${NAME}

${NAME} :
	@make -C ${LIBFT}
	${CC} ${FLAG} ${SRCS} ${LIBFT}/libft.a -o ${NAME}

clean :
	@make clean -C ${LIBFT}

fclean :
	@make fclean -C ${LIBFT}
	rm -f ${NAME}

re:	fclean all
