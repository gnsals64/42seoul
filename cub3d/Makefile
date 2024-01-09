# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 16:37:06 by junhyupa          #+#    #+#              #
#    Updated: 2023/05/26 16:00:19 by junhyupa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc -g -fsanitize=address
FLAG = -Wall -Werror -Wextra -g -fsanitize=address

INC = -I ./inc

#MLX_DIR = ./minilibx-linux
#MLX_EXEC = -L{MLX_DIR} -lmlx -lm -lX11 -lXext
MLX_DIR = ./
MLX_EXEC = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

LIBFT := ./libft/libft.a
LIBFT_DIR := ./libft/

FILES = $(addprefix ./src/, dda draw hook init_raycast init loop main raycast init_img key_func)
SRCS = $(FILES:=.c)

PARSER_SRC := parse.c parse_map.c map_checker.c parse_option.c
PARSER_SRCS := $(addprefix ./parser/,$(PARSER_SRC))

UTIL_SRC := err.c free.c
UTIL_SRCS := $(addprefix ./utils/,$(UTIL_SRC))

GNL_SRC := get_next_line.c get_next_line_utils.c
GNL_SRCS := $(addprefix ./GNL/,$(GNL_SRC))
OBJS := $(SRCS:.c=.o) $(PARSER_SRCS:.c=.o) $(UTIL_SRCS:.c=.o) $(GNL_SRCS:.c=.o)

all : ${NAME}

%.o : %.c
	$(CC)  ${INC} -c $< -o  $@

${NAME} : $(OBJS) $(LIBFT)
	${CC}  $^ ${MLX_EXEC}  ${INC} -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR)

clean :
	@make clean -C ${LIBFT_DIR}
	@rm -f $(OBJS)

fclean :
	@make fclean -C ${LIBFT_DIR}
	@make clean
	@rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re
