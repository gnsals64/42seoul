NAME = bureaucrat
CC = c++
FLAG = -Wall -Werror -Wextra -std=c++98
SRC_FILE = $(addprefix , main Bureaucrat AForm ShrubberyCreationForm RobotomyRequestForm PresidentialPardonForm)
SRCS = ${SRC_FILE:=.cpp}
OBJS = ${SRC_FILE:=.o}

all : $(NAME)

%.o : %.cpp
	${CC} ${FLAG}  -c $< -o $@

$(NAME) : $(OBJS)
	${CC} ${FLAG} $(OBJS) -o $(NAME)

clean :
	@rm -f ${OBJS}

fclean :
	@rm -f ${OBJS}
	@rm -f ${NAME}

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re
