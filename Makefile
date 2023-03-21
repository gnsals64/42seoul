# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 21:41:07 by hunpark           #+#    #+#              #
#    Updated: 2023/03/21 19:28:08 by hunpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAG = -Wall -Werror -Wextra
INC = -I ./inc
COMFILE_FLAGS = -lreadline -L$(shell brew --prefix readline)/lib
INCLUDE_FLAGS = -I$(shell brew --prefix readline)/include

PARSER = $(addprefix parser/, parser tokenizer_utils tokenizer lexer isspecial lexer_utils make_argv make_argv_utils rm_quote change_env_utils change_env)
UTILS = $(addprefix utils/, utils ft_exit_error)
BUILT_IN = ${addprefix built-in/, builtin_utils ft_cd ft_echo ft_env ft_exit ft_export ft_pwd ft_unset}
EXECUTE = ${addprefix execute/, builtin execute ft_error ft_fork ft_redirect}
FILES = $(addprefix src/, init minishell signals env ft_free ${UTILS} ${PARSER} ${BUILT_IN} ${EXECUTE})

SRCS = ${FILES:=.c}

LIBFT = ./src/libft

all : ${NAME}

${NAME} :
	@make -C ${LIBFT}
	${CC} ${FLAG} ${SRCS} ${COMFILE_FLAGS} ${INCLUDE_FLAGS} ${INC} -lreadline ${LIBFT}/libft.a -o ${NAME}

clean :
	@make clean -C ${LIBFT}
	rm -f bonus

fclean :
	@make fclean -C ${LIBFT}
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re
