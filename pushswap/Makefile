# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 10:58:17 by hunpark           #+#    #+#              #
#    Updated: 2023/02/23 15:25:11 by hunpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CHECKER = checker
CC = cc
FLAG = -Wall -Werror -Wextra
SRCS = ./src/deque.c \
		./src/push_swap.c \
		./src/utils.c \
		./src/fn_swap_push.c \
		./src/fn_rotate.c \
		./src/fn_mix.c \
		./src/parsing.c \
		./src/parsing_utils.c \
		./src/error.c \
		./src/sort.c \
		./src/greedy.c \
		./src/greedy_utils.c \

SRCS_BN = ./src_bn/checker.c \
			./gnl/get_next_line.c \
			./gnl/get_next_line_utils.c \
			./src/deque.c \
			./src/utils.c \
			./src_bn/fn_swap_push_bn.c \
			./src_bn/fn_rotate_bn.c \
			./src_bn/fn_mix_bn.c \
			./src/parsing.c \
			./src/parsing_utils.c \
			./src/error.c \
			./src/sort.c \

LIBFT = ./libft

all : ${NAME}

${NAME} :
	@make -C ${LIBFT}
	${CC} ${FLAG} ${SRCS} ${LIBFT}/libft.a -o ${NAME}

bonus :
	touch bonus
	@make -C ${LIBFT}
	${CC} -g ${FLAG} ${SRCS_BN} ${LIBFT}/libft.a -o ${CHECKER}

clean :
	@make clean -C ${LIBFT}
	rm -f bonus

fclean :
	@make fclean -C ${LIBFT}
	rm -f ${NAME}
	rm -f ${CHECKER}
	rm -f bonus

re : fclean all

.PHONY : all clean fclean re
