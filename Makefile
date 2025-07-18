NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes -Imlx -Ilibft -Iget_next_line -g
# === PATHS ===
SRC_DIR		= src
LIBFT_DIR	= libft
MLX_DIR		= mlx
GNL_DIR     = get_next_line
# === FILES ===
GNL_SRC		= $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
SRC_FILES	= $(shell find $(SRC_DIR) -name '*.c') $(GNL_SRC)
OBJ_FILES	= $(SRC_FILES:.c=.o)

LIBFT		= $(LIBFT_DIR)/libft.a
MLX_LIB		= -L$(MLX_DIR) -lmlx -lXext -lX11

# === RULES ===
all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(GNL) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT) $(MLX_LIB) -lm

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -f $(OBJ_FILES)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re