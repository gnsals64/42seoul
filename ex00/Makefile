NAME = convert
CC = c++
FLAG = -Wall -Werror -Wextra #-fsanitize=address
SRC_FILE = $(addprefix ./, main Convert)
SRCS = ${SRC_FILE:=.cpp}
OBJS = ${SRC_FILE:=.o}

all : $(NAME)

%.o : %.cpp
	${CC}  -c $< -o $@

$(NAME) : $(OBJS)
	${CC} ${FLAG} $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS) 

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
