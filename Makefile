##
## EPITECH PROJECT, 2018
## makefile
## File description:
## This file is used for compilation of every files to make a binary file.
##
MAIN_FILE		=	./src/main.c
SRC				=	./src/error.c			\
					./src/connection.c		\
					./src/authentication.c	\

CLIENT		=	./bootstrap/client.c		\

SERVER		=	./src/server/main.c

NAME			=	myftp

SRC_TEST		=	./tests/test.c
NAME_TEST		=	test_nm

INCLUDE_PATH	=	./include/

CFLAGS			=	-Wall -Wextra -I $(INCLUDE_PATH)

OBJ				=	$(SRC:.c=.o)
OBJ_MAIN		=	$(MAIN_FILE:.c=.o)

all: $(NAME)

client:
	gcc -o client $(CLIENT) $(CFLAGS)

server:
	gcc -o server $(SERVER) $(CFLAGS)

$(NAME): $(OBJ) $(OBJ_MAIN)
	gcc -o $(NAME) $(OBJ) $(OBJ_MAIN) $(CFLAGS)

debug:
	gcc -o $(NAME) $(SRC) $(MAIN_FILE) $(CFLAGS) -g

tests_run: all
	gcc $(CFLAGS) $(SRC_TEST) -o test_nm

clean:
	@rm -f $(OBJ) $(OBJ_MAIN) $(LIB_NAME)

fclean:
	@rm -f $(OBJ) $(OBJ_MAIN) $(LIB_NAME)
	@rm -f $(NAME) $(NAME_TEST)

re:	fclean all

.PHONY:	all clean fclean re debug client server
