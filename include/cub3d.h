/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:37:25 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/08 19:18:52 by pmorello         ###   ########.fr       */
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

#ifndef O_DIRECTORY
#define O_DIRECTORY 00200000
#endif

#ifndef BONUS
#define BONUS 0
#endif

/* MINIMAP */
#define MMP_SIZE 128

/* ERROR*/
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

/* STRUCTURES */
typedef struct s_image
{
	void	*image; //Es un punter que guarda la imatge, per poder ferlo servir altres llocs del codi
	int		*addr; //Es un punter que apunta a la memoria on es guarden els pixels de la imatge
	int		pixel_bits; //Guarda quants bits ocupa cada pixel, per saber quants bytes cal llegir o escriure per cada pixel
	int		size_line; //Serveix per calcular on comenca la seguents linia de pixel dins la memoria
	int		endian; //Indica l'ordre dels bytes dins de cada pixel
} t_image;

typedef struct	s_textures
{
	char	*N; //Ruta a la imatge de la textura NORD
	char	*S; //Ruta a la imatge de la textura SUD
	char	*E; //Ruta a la imatge de la textura EST
	char	*W; //Ruta a la imatge de la textura OEST
	int		*floor; //Es un punter, que apunta a una direccio de mem, on es guarden amb arrays diferents, el numero que indican el color del terra
	int		*ceiling; //Es un punter, que apunta a una direccio de mem, on es guarden amb arrays diferents, el numero que indican el color del cel
	int		index; //Es un index, per navegar per les textures. EX: Index 1 = textura NORD.
	int		size; //Mida de la textura, 64 alcada* 64 amplada, pixels
	//---------------------------------------------------------------
	int		x; 
	int		y;
	/* 
	int x, y. Son les coordenades dins de la textura, 
	per poder saber quin pixexl pintar en pantalla
	
	X, es per marcar la coordenada horitzontal (Esquerra,dreta)
	Y, per marcar la coordenada vertical (Adalta, abaix)

	EX: en una textura 64x64, diem que el raig toca una paret, ha de saber
	en quin punt de la paret ha impactat per saber quin pixel exacta dibuixar
	*/

	//--------------------------------------------------------------------
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	/*
	Color del terra i del sostre, en format hexadecimal. Fem servir el format hexa,
	pq aixi podem guardar el color en u sol enter, de manera que es mes eficient
	a la hora de pintar en pantalla
	*/
	//----------------------------------------------------------
	
	double	pass;
	double	pos;
	double	step;

	/*
	STEP, indica quant avanco per cada pixel. 
	EX: La finestra es de 200pixels, pero la textura fa 64,
	llavors, cada cop que pintem un pixel de la textura en la finestra, 
	el proxim pixel a pintar estara = 64 / 200 = 0.32 pixels de distancia
	
	POS, indica en quin punt de la textura comena dibuixarse dins la finestra,
	EX: si comencas a dibuixar dins el pixel 150 de la finestra, llavors el primer pixel
	de la textura que es dibuixara, sera el pixel 10 de la textura. 
	
	PASS, avancant dins la textura poc a poc i proporcionalment, per dibuixar la textura
	de manera correcta, segons limpacte del raig
	*/

}t_text;

typedef struct	s_map
{
	int		fd; //file descriptor, es un numero que es indica si llegim, escrivim... en un fitxer
	int		line_count; //Numero total de lineas que formen el mapa
	int		height; //Alcada del mapa en lineas
	int		width; //Amplada del mapa en columnes
	int		end_map; //Punt final del mapa, on sacaba
	char	*path; //Ruta a on es guarda el fitxer del mapa
	char	**file; //Fitxer que conte la informacio completa (paret, jugador, terra, colors...) del mapa, linea per linea

}t_map;

typedef struct	s_player
{
	char	dir; //Orientacio de on mirara el jugador al inciar el programa
	double	dir_x; //En quina dirrecio mira el jugador en el eix X
	double	dir_y; //En quina dirrecio mira el jugador en el eix Y
	double	pos_x; //En quina posicio esta el jugador en el eix X
	double	pos_y; //En quina posicio esta el jugador en el eix Y

	//---------------------------------------------------------
	double	cam_x;
	double	cam_y;
	/*
	CAM, serveix per marcar quin es el camp de visio del jugador, que pot veure el jugador
	El camp de visio sera la perpendicular de la posicio del jugador.
	per saber si es perpendicular, 
	vector original (1, 1)
	vector a saber (1, -1)
	(1,1) * (1, -1) = 1 * 1 + 1 * (-1) = 1 + (-1) = 1 - 1 = 0, si dona 0, vol dir que son
	perpendiculars
	
	LLavors si la direccio del jugador es (1, 1), adalt - dret, podra mirar fins (adalt, esquerra ), no podra mirar cap abaix, ni darrera,etc...
	*/
	double	s_rotate; //velocitat de rotacio
	int		move_x; //Moviment actual en X
	int		move_y; //MOviment actual en Y
	int		rotate; //Indica si el jugador rota
	int		has_moved; //Indica si el jugador sha mogut

}t_player;

typedef struct	s_ray
{
	double	cam_x; //De la vista del jugador, el que veu en pantalla, a on pot impactar,passar, tocar el raig
	double	dir_x; //Direccio del raig en el eix X, dins del mapa
	double	dir_y; //Direcio del raig en el eiz Y, dins del mapa
	double	map_x; //Posicio actual del raig en el eix X, dins del mapa
	double	map_y; //Posicio actual del raig en el eix Y, dins del mapa
	double	step_x;
	double	step_y;

	//---------------------------------------
	
	double	ngd_x;
	double	ngd_y;
	double	ncd_x;
	double	ncd_y;
	
	/*
	Tenim un mapa

	+----+----+----+
	| *	 |    |    |   -> GRAELLA
	----------------
	| = linea de la graella	
	* = punt original del raig
	NGD, es la distancia desde el punt original del raig, fins que impacti en una linea
	de la graella

	NCD, seria la distancia que creuara el raig dins de una cela en x o y

	+----+
	|    | -> Casella, 
	+----+

	*/
	//----------------------------
	
	double	wall_dist; //la distancia del raig a la paret
	double	wall_x; //en quin punt de la paret a impapctat el raig
	int		side; //per saber si la paret que hem tocat es horitzontal o vertical, vist desde un punt de vista zenital
	int		line_height; //alcada d ela linea de la paret a dibuixar
	int		draw_start; //En quin pixel de la finestra es comenca a dibuixar la paret
	int		draw_end; //En quin pixel de la finestra para de dibuixar

}t_ray;

typedef struct s_mmap
{
	/* 
	Tile, es una casella quadrada del mapa
	el tile_size, es quants pixels ocupa cada quadre a la hora de dibuixarse el joc

	Els offset son desplaçament dins del mapa gran per determinar quines parts del mapa
	es mostren en el minimapa
	*/
	
	char	**map; //Guarda la info del mapa gran i es posen nous caracter per represetnar el minimapa
	int		size; //Tamany del minimapa en tiles
	int		offset_x; //desplacament en X del mapa per centrar la vista del jugador
	int		offset_y; //desplacament en Y del mapa per centrar la vista del jugador
	int		view_dist; //quantes caselles hi hauran a cada costat del jugador en el minimapa
	int		tile_size; //la mida de pixels d'un tile
	t_image	*img; //imatge on es dibuixa el minimapa

}t_mmap;

typedef struct	s_general
{
	void	*mlx; //es un punter per referenciar la llibreria mlx
	void	*win; //es un punter per referenciar la finestra o es veura el joc
	char	**map; //mapa del joc en caracters (1,0,P....)
	int		win_height; //la alcada de la finestra (i)
	int		win_width; //la ampla de la finestra (j)
	int		**text; //les textures carregades com arrays
	int		**txt_pixels; //pixels de les textures

	t_image	img; //informacio de la imatge
	t_map	s_map; //informaico del mapa
	t_text	txt; //informacio de les textures
	t_ray	ray; //informacio del raycasting
	t_player	player; //informacio del jugador
	t_image  mmap;

}t_general;

/* FUNCTIONS */

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
void	set_color_pixel(t_image *i, int x, int y, int color);
void	render_images(t_general *g);

//utils
int		error(char *msg, char *err, int c);
int		quit(t_general *g);
void	n_exit(t_general *g, int c);
void	clean_exit(t_general *g, int c);
void	free_tab(void **tab);
int		free_data(t_general *g);
int		check_blank_space(char c);
size_t	biggest_line(t_map *m, int i);

//bonus
void	render_mmap(t_general *g, t_image *i);
void	minimap_image(t_general *g, t_mmap*mmp, t_image *i);


#endif
