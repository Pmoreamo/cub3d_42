# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 17:14:11 by pafranco          #+#    #+#              #
#    Updated: 2025/08/11 17:54:12 by pafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#PROJECT INFO
NAME = cub3d
NAME_BONUS = cub3d_bonus

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
				$(SRC_DIR)/init/init_structes.c $(SRC_DIR)/parsing/create_map.c \
				$(SRC_DIR)/parsing/parse_arg.c $(SRC_DIR)/parsing/parse_color.c \
				$(SRC_DIR)/parsing/parse_info.c $(SRC_DIR)/parsing/parse_map_borders.c \
				$(SRC_DIR)/parsing/parse_textures.c $(SRC_DIR)/parsing/parse_utils.c \
				$(SRC_DIR)/player/player_dir.c $(SRC_DIR)/player/player_move.c \
				$(SRC_DIR)/player/player_rotate.c $(SRC_DIR)/utils/error.c \
				$(SRC_DIR)/utils/exit.c $(SRC_DIR)/utils/free.c \
				$(SRC_DIR)/utils/color_pixel.c  $(SRC_DIR)/utils/append.c\

NORMAL_FILES=	$(SRC_DIR)/render/render.c $(SRC_DIR)/parsing/get_data.c \
				$(SRC_DIR)/render/raycasting.c $(SRC_DIR)/render/textures.c \
				$(SRC_DIR)/init/init_textures.c $(SRC_DIR)/player/player_pos.c \
				$(SRC_DIR)/player/inputs_key.c $(SRC_DIR)/parsing/parse_map.c \

BONUS_FILES	=	$(SRC_DIR)/bonus/render/render.c $(SRC_DIR)/bonus/parsing/get_data.c \
				$(SRC_DIR)/bonus/render/raycasting.c $(SRC_DIR)/bonus/render/textures.c \
				$(SRC_DIR)/bonus/init/init_textures.c $(SRC_DIR)/bonus/player/player_pos.c \
				$(SRC_DIR)/bonus/doors.c $(SRC_DIR)/bonus/minimap_image.c \
				$(SRC_DIR)/bonus/minimap.c $(SRC_DIR)/bonus/inputs_key_bonus.c \
				$(SRC_DIR)/bonus/parsing/parse_map.c \

HEAD		=	include/cub3d.h

#OBJECTS
OBJS_FILES = $(SRCS_FILES:.c=.o)
OBJS_NORMAL = $(NORMAL_FILES:.c=.o)
OBJS_BONUS = $(BONUS_FILES:.c=.o)

#LIBRARIES
LIBFT = $(LIBFT_DIR)/libft.a

#RULES
all: Makefile $(LIBFT) $(NAME) 

$(NAME): Makefile $(LIBFT) $(OBJS_FILES) $(OBJS_NORMAL) $(HEAD)
	$(CC) $(CFLAGS) $(OBJS_FILES) $(OBJS_NORMAL) -o $(NAME) $(LIBFT) $(MLX_FLAGS)

$(NAME_BONUS): Makefile $(LIBFT) $(OBJS_FILES) $(OBJS_BONUS) $(HEAD)
	$(CC) $(CFLAGS) $(OBJS_FILES) $(OBJS_BONUS) -o $(NAME) $(LIBFT) $(MLX_FLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS_FILES) $(OBJS_BONUS) $(OBJS_NORMAL)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME) $(NAME_BONUS)

bonus:	$(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
