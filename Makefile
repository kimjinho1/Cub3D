# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 22:32:57 by jinhokim          #+#    #+#              #
#    Updated: 2022/12/15 22:33:21 by jinhokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_DIR	:= ./srcs
INC_DIR	:= ./includes
OBJ_DIR	:= ./objects
LIB_DIR	:= ./libft

SRC = main.c \
		gnl.c \
		gnl_utils.c \
		utils.c \
		element_check.c \
		map_check.c \
		map_check2.c \
		raycast.c \
		draw.c \
		move.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L ./mlx -lmlx -framework OpenGL -framework Appkit #Mac
MLX_WIN_FLAGS = -lbsd -lmlx -lXext -lX11 -lm #window
RM = rm -rf

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -I$(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(OBJ) $(CFLAGS) -L $(LIB_DIR) -l ft $(MLX_FLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all
