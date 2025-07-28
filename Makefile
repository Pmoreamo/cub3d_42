NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iincludes -Imlx -Ilibft -g
BONUS		= 0
# === PATHS ===
SRC_DIR		= src
LIBFT_DIR	= libft
MLX_DIR		= mlx

# === FILES ===
SRC_FILES	= $(shell find $(SRC_DIR) -name '*.c') $(GNL_SRC)
OBJ_FILES	= $(SRC_FILES:.c=.o)

LIBFT		= $(LIBFT_DIR)/libft.a
MLX_LIB		= -L$(MLX_DIR) -lmlx -lXext -lX11

# ===RULES====

OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Includes
INC			=	-I ./includes/\
				-I ./libft/\
				-I ./minilibx-linux/

# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/init
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/movement
	mkdir -p $(OBJ_PATH)/render
	mkdir -p $(OBJ_PATH)/debug
	mkdir -p $(OBJ_PATH)/exit

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm

# Libft rule
$(LIBFT):
	@$(MAKE) -sC $(LIBFT_PATH)

# MLX rule
$(MLX):
	@$(MAKE) -sC $(MLX_PATH)

bonus:
	@$(MAKE) all BONUS=1

# Clean up build files rule
clean:
	rm -rf $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean

# Remove program executable
fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

# Clean + remove executable
re: fclean all

.PHONY: all clean fclean re
