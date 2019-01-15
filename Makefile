NAME = avm

SRCS = srcs/main.cpp \
		srcs/Factory.cpp \
		srcs/VM.cpp \
		srcs/Exception.cpp \
		srcs/Lexer.cpp \

OBJ = $(SRCS:.cpp=.o)

CFLAGS = -std=c++11 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	clang++ $(CFLAGS) $(OBJ) -o $(NAME) -I includes

%.o: %.cpp
	clang++ $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re