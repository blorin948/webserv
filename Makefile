$(VERBOSE).SILENT:

SRCS	= GetResponse.cpp\
	ParseRequest.cpp\
	PostResponse.cpp\
	RouteConf.cpp\
	ServerConf.cpp\
	init.cpp\
	server_side1.cpp\
	utils.cpp\
	AutoIndexGenerator.cpp\
	CgiMaker.cpp\
	DeleteRequest.cpp\
	do_method.cpp\
	server_connection.cpp\
	parse.cpp\

OBJS	= $(SRCS:.cpp=.o)

CC =  clang++ -Wall -Wextra -Werror

RM = rm -f

NAME = Webserv

all:	$(NAME)

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
