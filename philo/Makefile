NAME = philosophers

SRC_FILES = main.c parsing.c utils.c

OBJ = $(SRC_FILES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-g3 #-fsanitize=address 

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "\033[32m[OK]\033[0m $(NAME) created!\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[32m[OK]\033[0m Compiled $<\n"

clean:
	@$(RM) $(OBJ)
	@printf "\033[32m[OK]\033[0m clean\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "\033[32m[OK]\033[0m fclean\n"

re: fclean all

.PHONY: all clean fclean re