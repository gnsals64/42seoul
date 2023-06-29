NAME = PhoneBook
CC = c++
FLAG = -Wall -Werror -Wextra -std=c++98
SRC_FILE = $(addprefix , Contact PhoneBook main)
SRCS = ${SRC_FILE:=.cpp}
OBJS = ${SRC_FILE:=.o}

all : ${NAME}

${NAME} : ${OBJS}
	@${CC} ${FLAG} ${SRCS} -o ${NAME}

clean :
	@rm -f ${OBJS}

fclean :
	@rm -f ${OBJS}
	@rm -f ${NAME}

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
