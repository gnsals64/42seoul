NAME = btc
CC = c++
FLAG = -Wall -Werror -Wextra -std=c++98 #-fsanitize=address
SRC_FILE = $(addprefix ./, main BitcoinExchange)
SRCS = ${SRC_FILE:=.cpp}
OBJS = ${SRC_FILE:=.o}

all : $(NAME)

%.o : %.cpp
	${CC} -g ${FLAG} -c $< -o $@

$(NAME) : $(OBJS)
	${CC} ${FLAG} $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
