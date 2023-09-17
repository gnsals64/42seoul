CXX			:=	c++ #-fsanitize=address -g
# CXXFLAGS	:= -std=c++98 -g
#-Wall -Wextra -Werror
LDFLAGS		:=

SRCS		:=	main.cpp\
				Worker.cpp\
				Transaction.cpp\
				Request.cpp\
				Location.cpp\
				LocationLexer.cpp\
				WorkerLexer.cpp\
				block_parser.cpp\
				token_parse_error.cpp\
				token_utils.cpp\
				tokenizer.cpp\
				Response.cpp\

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