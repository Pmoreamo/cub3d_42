#PROJECT INFO
NAME = cub3d
BONUS = 0

#DIRECTORIES 
SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = mlx
LIBFT_DIR = libft

#COMPILERS & FLAGS
CC = cc
INC = -Iinclude -I$(LIBFT_DIR) -I$(MLX_DIR)
CFLAGS = -Wall -Wextra -Werror -g $(INC)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

#DELETE
RM = rm -rf

#SOURCES
SRCS_FILES	=	$(SRC_DIR)/main.c $(SRC_DIR)/init/init_images.c \
				$(SRC_DIR)/init/init_structes.c $(SRC_DIR)/init/init_textures.c \
				$(SRC_DIR)/parsing/create_map.c $(SRC_DIR)/parsing/get_data.c \
				$(SRC_DIR)/parsing/parse_arg.c $(SRC_DIR)/parsing/parse_color.c \
				$(SRC_DIR)/parsing/parse_info.c $(SRC_DIR)/parsing/parse_map_borders.c \
				$(SRC_DIR)/parsing/parse_map.c $(SRC_DIR)/parsing/parse_textures.c \
				$(SRC_DIR)/parsing/parse_utils.c $(SRC_DIR)/player/inputs_key.c \
				$(SRC_DIR)/player/player_dir.c $(SRC_DIR)/player/player_move.c \
				$(SRC_DIR)/player/player_pos.c $(SRC_DIR)/player/player_rotate.c \
				$(SRC_DIR)/render/raycasting.c $(SRC_DIR)/render/render.c \
				$(SRC_DIR)/render/textures.c $(SRC_DIR)/utils/error.c \
				$(SRC_DIR)/utils/exit.c $(SRC_DIR)/utils/free.c \

BONUS_FILES	=	$(SRC_DIR)/bonus/minimap_image.c $(SRC_DIR)/bonus/minimap.c \

#OBJECTS
OBJS_FILES = $(SRCS_FILES:.c=.o)
OBJS_BONUS = $(BONUS_FILES:.c=.o)

#LIBRARIES
LIBFT = $(LIBFT_DIR)/libft.a

#RULES
all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJS_FILES) $(OBJS_BONUS)
	$(CC)	$(CFLAGS)	-o	$(NAME)	$(OBJS_FILES)	$(OBJS_BONUS)	$(LIBFT)	$(MLX_FLAGS)

%.o:$(SRC_DIR)/%.c
	$(CC)	$(CFLAGS)	-DBONUS=$(BONUS)	-c	$<	-o	$@

$(LIBFT):
	@$(MAKE)	-C	$(LIBFT_DIR)

clean:
	@$(MAKE)	-C	$(LIBFT_DIR)	clean
	$(RM)	$(OBJ_DIR)

fclean:clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM)	$(NAME)

bonus: make all BONUS=1

re: fclean all

.PHONY: all clean fclean re