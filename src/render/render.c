/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:41 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/09 19:16:08 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_color_pixel(t_image *i, int x, int y, int color)
{
	int		pixel; //index per marcar en quin pixel estem

	pixel = y * (i->size_line / 4) + x;
	/* 1 pixel = 4 bytes, per saber quants	pixels hi han en una linea, 
	hem de agafar els bytes de la linea (size_line) / 4 (bytes per pixel), tindrem el numero de pixels
	per saber quin pixel exacte es, hem de multiplicar per Y i sumar X */
	i->addr[pixel] = color; 
	/* accedim a ADDR que es un array on es guarda els pixels en la memoria.
	entrem cada PIXEL del array i asignem el COLOR */
}

void	paint_pixel_in_frame(t_general *g, t_image *i, int x, int y)
{
	/* g, es la estrctura amb informacio del joc
	i, es el frame buffer, on estem pintan
	x,y son les coordenades del pixel dins la finestra */
	
	if (g->txt_pixels[y][x] > 0) 
	/* va iterant en el mapa, si en algun punt del mapa es superior a 0 (1)
	pintara aquell punt, amb el color */
		set_color_pixel(i, x, y, g->txt_pixels[y][x]);
	else if (y < g->win_height / 2) 
		set_color_pixel(i, x, y, g->txt.hex_ceiling);
	/* si el punt y es mes petit que la meitat de lacada de la finestra vol dir 
	que es el cel, el pintara amb el color guardat a txt.hex_ceiling */
	else
	/* si es la resta, vol dir que se terra i el pintara amb txt.hex_floor */
		set_color_pixel(i, x, y, g->txt.hex_floor); 
}

static void	put_frame_in_window(t_general *g)
{
	t_image		i;
	int			x;
	int			y;

	i.image = NULL;
	init_img(g, &i, g->win_width, g->win_height); //iniciem la imatge
	y = 0;
	while (y < g->win_height)
	{
		x = 0;
		while (x < g->win_width)
		{
			paint_pixel_in_frame(g, &i, x, y);
			/* mentres els valors de x i y siguin inferiors a les mides de la finestra, pintarem */
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g->mlx, g->win, i.image, 0, 0);
	/* posem les imatges en la finestra */
	mlx_destroy_image(g->mlx, i.image);
	/* destruim per alliberar memoria */
}

void	draw_raycast(t_general *g)
{
	init_textures_pixels(g);
	init_s_ray(&g->ray);
	raycasting(g, &g->player);
	put_frame_in_window(g);
}

void	render_images(t_general *g)
{
	draw_raycast(g);
}

int	render(t_general *g)
{
	g->player.has_moved += move_player(g);
	if (g->player.has_moved == 0)
		return (0);
	render_images(g);
	return (0);
}
