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

# Split 후에 나온 output[0] 검사

# (6개 중 하나가 아니거나, 이미 나온 속성, 속성의 값들이 매칭되지 않을 경우, invalid한 값이 들어온 경우)
# NO ./path_to_the_north_texture
# SO ./path_to_the_south_texture
# WE ./path_to_the_west_texture
# EA ./path_to_the_east_texture
# F 220,100,0
# C 225,30,0

# 맵	검사
# 첫번째 사이클
# 1,0,[좌표] 아닌거 나오면 에러(nswe 중복시 에러), 최장 가로-세로 길이 구하기

# -입력된 맵 변환 후-

# 두번째 사이클
# 닫힌 맵인지 검사
# 만약 현재 맵의 값이 0이면 4방향 검사하고, 

# 111
# 1  1
# 111

# 000
# 0  0
# 000


# 맵 요소를 하나씩 검사함

# 1. 0일 경우 - 4방 검사
# 2. NSEW일 경우 - 0과 같은 판정, 여러개 나올시 엘
# 3. 공백일 경우 - 