# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 21:23:27 by hunpark           #+#    #+#              #
#    Updated: 2022/09/30 04:57:28 by hunpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar -rcs
INC = inc
INC_BN = inc_bonus
SRCS = ft_printf_bonus.c \
		src_01/ft_print_char.c \
		src_01/ft_print_it.c \
		src_01/ft_print_str.c \
		src_01/ft_print_pointer.c \
		src_01/ft_print_decimal_01.c \
		src_01/ft_print_decimal_02.c \
		src_01/ft_print_u_int_01.c \
		src_01/ft_print_u_int_02.c \
		src_01/ft_print_hex_01.c \
		src_01/ft_print_hex_02.c \
		src_01/ft_print_per.c\
		src_02/ft_etc.c \
		src_02/ft_is.c \
		src_02/ft_parsing.c \
		src_02/ft_uitoa.c \
		src_02/ft_uitox.c \

SRCS_BN = ft_printf_bonus.c \
		src_bonus_01/ft_print_char_bn.c \
		src_bonus_01/ft_print_it_bn.c \
		src_bonus_01/ft_print_str_bn.c \
		src_bonus_01/ft_print_pointer_bn.c \
		src_bonus_01/ft_print_decimal_01_bn.c \
		src_bonus_01/ft_print_decimal_02_bn.c \
		src_bonus_01/ft_print_u_int_01_bn.c \
		src_bonus_01/ft_print_u_int_02_bn.c \
		src_bonus_01/ft_print_hex_01_bn.c \
		src_bonus_01/ft_print_hex_02_bn.c \
		src_bonus_01/ft_print_per_bn.c\
		src_bonus_02/ft_etc_bn.c \
		src_bonus_02/ft_is_bn.c \
		src_bonus_02/ft_parsing_bn.c \
		src_bonus_02/ft_uitoa_bn.c \
		src_bonus_02/ft_uitox_bn.c \


OBJS = $(SRCS:.c=.o)
OBJS_BN = $(SRCS_BN:.c=.o)

ifdef WITH_BONUS
	INC = $(INC)
else
	INC = $(INC_BN)
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@ -I $(INC)

$(NAME) : $(OBJS)
	cp libft/libft.a $(NAME)
	$(AR) $(NAME) $(OBJS)

bonus : $(OBJS_BN)
	cp libft/libft.a $(NAME)
	$(AR) $(NAME) $(OBJS_BN)

clean :
	$(RM) $(OBJS) $(OBJS_BN)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
