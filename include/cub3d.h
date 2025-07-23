/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:37:25 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/23 11:01:00 by pmorello         ###   ########.fr       */
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
void	init_s_player(t_player *p);
void	init_s_textures(t_text *t);
void	init_s_map(t_map *m);
void	init_s_image(t_image *i);
void	init_s_ray(t_ray *r);
void	init_s_general(t_general *g);
void	init_img(t_general *g, t_image *i, int width, int height);
void	init_textures_img(t_general *g, t_image *i, char *p);
void	init_mlx(t_general *g);
void	init_textures(t_general *g);
void	init_input_keys(t_general *g);
void	init_player_dir(t_general *g);
void	init_textures_pixels(t_general *g);

//parse
int		check_file(char *arg, int type);
void	check_info(char *path, t_general *g);
int		get_file_info(t_general *g, char **map);
int		check_map_validity(t_general *g, char **m_tab);
int		check_sides(t_map *m, char **new_m);
int		check_textures(t_general *g, t_text *t);
int		fill_color_textures(t_general *g, t_text *t, char *line, int j);
int		create_map(t_general *g, char **file, int i);


//player
int		move_player(t_general *g);
int		validate_move(t_general *g, double new_x, double new_y);
int		player_rotate(t_general *g, double dir);

//render
int		raycasting(t_general *g, t_player *p);
int		render(t_general *g);
void	draw_raycast(t_general *g);
void	update_textures_pixels(t_general *g, t_text *t, t_ray *r, int x);


//utils
int		error(char *msg, char *err, int c);
int		quit(t_general *g);
void	n_exit(t_general *g, int c);
void	clean_exit(t_general *g, int c);
void	free_tab(void **tab);
int		free_data(t_general *g);
int		check_blank_space(char c);
size_t	biggest_line(t_map *m, int i);

#endif
