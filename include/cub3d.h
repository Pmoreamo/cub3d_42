/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:37:25 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 14:35:28 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H


#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <fcntl.h>
#include <math.h>

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"

# define ERR_FILE_NOT_CUB " Not a .cub file"
# define ERR_FILE_NOT_XPM " Not an .xpm file"
# define ERR_FILE_IS_DIR " Is a directory"
# define ERR_FLOOR_CEILING " Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR " Invalid floor RGB color"
# define ERR_COLOR_CEILING " Invalid ceiling RGB color"
# define ERR_INVALID_MAP " Map description is either wrong or incomplete"
# define ERR_INV_LETTER " Invalid character in map"
# define ERR_NUM_PLAYER " Map has more than one player"
# define ERR_TEX_RGB_VAL " Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING " Missing texture(s)"
# define ERR_TEX_INVALID " Invalid texture(s)"
# define ERR_COLOR_MISSING " Missing color(s)"
# define ERR_MAP_MISSING " Missing map"
# define ERR_MAP_TOO_SMALL " Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS " Map is not surrounded by walls"
# define ERR_MAP_LAST " Map is not the last element in file"
# define ERR_PLAYER_POS " Invalid player position"
# define ERR_PLAYER_DIR " Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC " Could not allocate memory"
# define ERR_MLX_START " Could not start mlx"
# define ERR_MLX_WIN " Could not create mlx window"
# define ERR_MLX_IMG " Could not create mlx image"

typedef struct s_image
{
	void	*image;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
} t_image;

typedef struct	s_textures
{
	char	*N;
	char	*S;
	char	*E;
	char	*W;
	int		*floor;
	int		*ceiling;
	int		index;
	int		size;
	int		x;
	int		y;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	double	pass;
	double	pos;
	double	step;

}t_text;

typedef struct	s_map
{
	int		fd;
	int		line_count;
	int		height;
	int		width;
	int		end_map;
	char	*path;
	char	**file;

}t_map;

typedef struct	s_player
{
	char	dir;
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	cam_x;
	double	cam_y;
	double	s_rotate;
	int		move_x;
	int		move_y;
	int		rotate;
	int		has_moved;

}t_player;

typedef struct	s_ray
{
	double	cam_x;
	double	dir_x;
	double	dir_y;
	double	map_x;
	double	map_y;
	double	step_x;
	double	step_y;
	double	ngd_x;
	double	ngd_y;
	double	ncd_x;
	double	ncd_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;

}t_ray;

typedef struct	s_general
{
	void	*mlx;
	void	*win;
	char	**map;
	int		win_height;
	int		win_width;
	int		**text;
	int		**txt_pixels;

	t_image	img;
	t_map	s_map;
	t_text	txt;
	t_ray	ray;
	t_player	player;

}t_general;

//init
void	init_s_general(t_general *gen);
void	init_s_image(t_image *img);
void	init_s_map(t_map *map);
void	init_s_textures(t_text *txt);
void	init_s_ray(t_ray *ray);
void	init_mlx(t_general *gen);

//raycastin
int		render(t_general *gen);
void	init_textures_pixels(t_general *gen);
void	update_textures_pixels(t_general *gen, t_text *txt, t_ray *ray, int x);
void	paint_pixel_in_frame(t_general *gen, t_image *img, int x, int y);
int		raycasting(t_general *gen, t_player *player);

//error
int		error(char *msg, char *er, int c);
int		error_detail(int detail, char *er, int c);


//free
void	free_tab(void **tab);
int		free_data(t_general *gen);

//parsing
int	check_file(char *arg, int type);
int	create_map(t_general *gen, char **file, int i);
int	check_map_validity(t_general *gen, char **map_tab);
int	get_file_info(t_general *gen, char **map);
int	check_sides(t_map *map, char **n_map);
int	check_textures(t_general *gen, t_text *txt);
int	fill_color_textures(t_general *gen, t_text *txt, char *line, int j);
void	check_info(char *path, t_general *gen);

//parsing_utils
int	check_blank_space(char c);
size_t	biggest_line(t_map *map, int i);

//exit
void	n_exit(t_general *gen, int code);
void	clean_exit(t_general *gen, int code);
int	quit(t_general *gen);

//player
void	init_input_keys(t_general *gen);
void	init_player_dir(t_general *gen);
int		validate_move(t_general *gen, double new_x, double new_y);
int		move_player(t_general *gen);
int		player_rotate(t_general *gen, double dir);



void	init_img(t_general *gen, t_image *img, int	width, int	height);
void	init_textures_img(t_general *gen, t_image *ing, char *path);
int	*save_xpm_to_mem(t_general *gen, char *path);
void	init_textures(t_general *gen);

#endif
