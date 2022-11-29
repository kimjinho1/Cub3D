NAME = cub3d

SRC_DIR	:= ./srcs
INC_DIR	:= ./includes
OBJ_DIR	:= ./objects
LIB_DIR	:= ./libft

SRC = main.c \
		utils.c \
		gnl.c \
		gnl_utils.c \
		parsing.c \
		draw.c \
		move.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L ./mlx -lmlx -framework OpenGL -framework Appkit
RM = rm -rf

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJ) -L $(LIB_DIR) -l ft

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -I$(INC_DIR) -o $@ -c $<

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all
