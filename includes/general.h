/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:22:10 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/16 14:34:31 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
#define GENERAL_H

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include "../get_next_line/get_next_line.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/keysym.h>
#include <stdbool.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <fcntl.h>
#include <math.h>

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define ERR_USAGE " ./cub3d <path/to/map.cub>"

# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid ceiling RGB color"
# define ERR_INVALID_MAP "Map description is either wrong or incomplete"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture(s)"
# define ERR_TEX_INVALID "Invalid texture(s)"
# define ERR_COLOR_MISSING "Missing color(s)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"


typedef struct s_image
{
    void    *image; //puntero en donde esta la IMAGEN guardada en la MEMORIA
    int     *addr; //puntero en donde estan los PIXELES de la IMAGEN en la MEMORIA, sirve para acceder y modificar cada pixel (color, tamaño, etc...)
    int     pixel_bits; //indica cuantos BITS ocupa cada PIXEL, sino el programa puede leer mal los datos
    int     size_line; //indica cuantos BYTES ocupa una linea de la IMAGEN en la MEMORIA
    int     endian; //indica como se guardan los BYTES en la MEMORIA, depende del orden su valor su puede interpretar

} t_image;

typedef struct s_map
{
    int     fd; //file descriptor
    int     line_count; //cuantas lineas tiene el MAPA
    char    *path; //donde esta guardado el MAPA
    char    **file; //para saber el contenido del MAPA, linea por linea.
    int     height; //alargada del MAPA
    int     width; //amplitud del MAPA
    int     end_map; //punto para saber si se ha llegado al final del MAPA.

} t_map;

typedef struct s_player
{
    char    exist; //marca para saber si hay PLAYER en el MAPA
    char    dir; //marca para saber que orientacion estara en PLAYER en el MAPA (N,S,E,W)
    double  dir_x; //marca la direccion donde estara mirando el PLAYER, en el eje X, del MAPA
    double  dir_y; //marca la direccion donde estara mirando el PLAYER, en el eje Y, del MAPA
    double  pos_x; //marca la posicion de PLAYER, en el eje X, del MAPA
    double  pos_y; //marca la posicion de PLAYER, en el eje Y, del MAPA
    double  plane_x; //marca el plano de camara del PLAYER, en el eje X
    double  plane_y; //marca el plano de camara del PLAYER, en el eje Y
    double  s_rotate; //marca la velocidad de rotacion de PLAYER
    int     move_x; //indica si PLAYER esta MOVIENDO en el eje X
    int     move_y; //indica si PLAYER esta moviendo en el eje Y
    int     rotate; //indica si PLAYER esta ROTANDO
    int     has_moved;

} t_player;

typedef struct s_texture
{
    char    *N; //path a la textura de la pared Norte
    char    *S; //path a la textura de la pared Sud
    char    *W; //path a la textura de la pared Oeste
    char    *E; //path a la textura de la pared Este
    int     *floor; //color de FLOOR en RGB
    int     *ceiling; //color de CELING en RGB
    unsigned long hex_floor; //color en HEXA, mas rapido de leer
    unsigned long   hex_ceiling; //color en HEXA; mas rapido de leer
    int     w_size; //la amplitud de la textura
    int     h_size; //la alargada de la textura
    int     size; //mezcla de w_szie y h_size
    double  pass; //indica cuantos PIXELS hemos avanzado en la TEXTRUA, cada vez que se dibbuja en la pantalla
    double  pos; //indica en que PIXEL de la TEXTURA esta, cuando se dibuja´
    int     index;
    double  step;
        
    int x; //coordenada dentro de la TEXTURA, para saber que PIXEL acceder
    int y; //coordenada dentro de la TEXTURA, para saber que PIXEL acceder

}  t_texture;

typedef struct s_ray
{
    double      camera_x; //posicion de CAMERA en EJE X
    double      dir_x; //direccion del RAYO en EJE X
    double      dir_y; //direccion del RAYO en EJE Y
    int         map_x; //coordenada del EJE X, donde esta el RAYO
    int         map_y; //coordenada del EJE Y, donde esta el RAYO
    int         step_x; //direccion a qual avanza el RAYO en EJE X
    int         step_y; //direccion a qual avanza el RAYO en EJE Y
    double      ngd_x; //Next Grid Dist, distancia hasta la siguiente quadricula en EJE X
    double      ngd_y; //Next Grid Dist, distancia hasta la sguiente quadricual en EJE Y
    double      ncd_x; //Next Cell Dist, distancia hasta la siguiente celda en EJE X
    double      ncd_y; //Next Cell Dist, distancia hasta la siguiente celda en EJE Y
    double      wall_dist; //Distancia hasta llegar a una PARED
    double      wall_x; //Posicion donde impacta RAYO en la PARED
    int         side; //Saber si es una PARED horizontal o vertical
    int         line_height; //Alarga de la linea que se dibujara en pantalla
    int         draw_start; //Donde empieza la PARED en la ventana
    int         draw_end; //Donde acaba la PARED en la ventana
} t_ray;


typedef struct s_general
{
    void    *mlx; //puntero a MLX
    void    *win; //puntero para referenciar la ventana
    int     win_height; //altura de WIN
    int     win_width; //anchura de WIN
    char    **map; //para guardar el MAPA

    int     **textures; //doble puntero, donde guardar las texturas de las paredes
    int     **text_pixels;

    t_image img; //STRUCT de IMAGE
    t_texture text; //STRUCT de TEXTURE
    t_player player; //STRUCT de PLAYER
    t_map   s_map; //STRUCT de MAP
    t_ray   ray; //STRUCT de RAYCASTING
    
} t_general;
/*-------------------------------------------------------------------------------*/
/* INIT */
//init_structures.c
void    init_s_images(t_image *img);
void    init_s_ray(t_ray *ray);
void    init_s_map(t_map *map);
void    init_s_player(t_player *player);
void    init_s_textures(t_texture *text);
void    init_s_general(t_general *gen);
//init_images.c
void    init_img(t_general *gen, t_image *img, int width, int height);
void    init_textures_img(t_general *gen, t_image *img, char *path);
int     *save_xmp_to_mem(t_general *gen, char *path);
void    init_textures(t_general *gen);
/*----------------------------------------------------------------------------*/
/* PLAYER */
//input_keys.c
void    init_input_hooks(t_general *gen);
//player_dir.c
void    init_player_dir(t_general *gen);
//player_move.c
int     move_player(t_general *gen);
//player_pos.c
int     validate_move(t_general *gen, double new_x, double new_y);
/*------------------------------------------------------------------------*/
/* RENDER */
//raycasting.c
int     raycasting(t_general *gen, t_player *player);
//render.c
//void    render_images(t_general *gen);
int     render(t_general *gen);
//textures.c
void    init_texture_pixels(t_general *gen);
void	update_texture_pixels(t_general *data, t_texture *text, t_ray *ray, int x);
/*----------------------------------------------------------------------------------*/
/* UTILS */
//error.c
int     error(char *detail, char *s, int code);
int     error_msg(int detail, char *s, int code);
//exit.c
void    clean_exit(t_general *gen, int code);
int     quit(t_general *gen);
void    n_exit(t_general *gen, int code);
//free_data.c
int     free_data(t_general *gen);
void    free_tab(void **tab);
//images_utils.c
void    set_color_pixel(t_image *img, int x, int y, int color);
//parse_utils.c
int     check_blanks(char c);
int     check_blank_space(char c);
int     check_blank_space_map(char **file, int i, int *j);
size_t  check_biggest_line_in_the_map(t_map *map, int i);
int     check_if_is_color(char *line, int j);
/*------------------------------------------------------------*/
/* PARSING */
//parse_texture.c
int     check_textures(t_general *gen, t_texture *text);
//parse_read_map.c
int     create_map(t_general *gen, char **file, int i);
//parse_map.c
int     check_map(t_general *gen, char **map);
//parse_data.c
void	check_data(char *path, t_general *gen);
//parse_color.c
int     fill_color_textures(t_general *gen, t_texture *text, char *line, int j);
//parse_args.c
int     check_file(char *file);
//get_data.c
int     get_file_data(t_general *gen, char **map);


#endif