# Nombre ejecutable
NAME = philo

# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -g3 -Wall -Wextra -Werror

# Directorios
SRC_DIR = src
OBJ_DIR = obj

# Archivos fuente
SRC =	main.c \
		init.c \
		utils.c \
		threads.c \
		parsing.c \
		monitor.c \
		routines.c \

# Archivos objeto
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Reglas make

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re