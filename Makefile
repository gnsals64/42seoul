CXX			:=	c++ -fsanitize=address -g
# CXXFLAGS	:= -std=c++98 -g
#-Wall -Wextra -Werror
LDFLAGS		:=

PARSER = $(addprefix parser/, BlockParser Location LocationLexer TokenParseError TokenUtils Tokenizer)
SERVER = $(addprefix server/, Worker WorkerLexer Webserv ServerUtils HandleData InitServer WorkerData)
HTTP = ${addprefix http/, Request Response CgiHandler}

FILES = $(addprefix src/, main  ${PARSER} ${SERVER} ${HTTP})

SRCS = ${FILES:=.cpp}

OBJS		:=	$(SRCS:.cpp=.o)

NAME		:= webserv

.SUFFIXES : .cpp .o
.cpp.o :
	$(CXX) $(CXXFLAGS) -c $< -o $@

all	: $(NAME)

$(NAME)	:	$(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

clean :
	rm -f $(OBJS)

fclean :
	make clean
	rm -f $(NAME)

re :
	make fclean
	make $(NAME)

.PHONY : all clean fclean re