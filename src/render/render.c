/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:41 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/08 20:22:07 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_color_pixel(t_image *i, int x, int y, int color)
{
	int		pixel; //index per marcar en quin pixel estem

	pixel = y * (i->size_line / 4) + x;
	/* 
	1 pixel = 4 bytes, per saber quants	pixels hi han en una linea, 
	hem de agafar els bytes de la linea (size_line) / 4 (bytes per pixel), tindrem el numero de pixels
	per saber quin pixel exacte es, hem de multiplicar per Y i sumar X
	*/
	i->addr[pixel] = color; 
	/* 
	accedim a ADDR que es on es guarda els pixels en la memoria.
	Accedim a cada PIXEL, i a cada pixel li asignem el COLOR
	*/
}

void	paint_pixel_in_frame(t_general *g, t_image *i, int x, int y)
{
	if (g->txt_pixels[y][x] > 0) //si les coordenades de les textures dels pixels son mes grans que 0, es a dir hi ha color
		set_color_pixel(i, x, y, g->txt_pixels[y][x]); //pinta els pixels amb el color de les textures
	else if (y < g->win_height / 2) //pinta la part superior, del color amb codi hexadecial de ceiling
		set_color_pixel(i, x, y, g->txt.hex_ceiling);
	else
		set_color_pixel(i, x, y, g->txt.hex_floor); //pintar el terra
}

static void	put_frame_in_window(t_general *g)
{
	t_image		i;
	int			x;
	int			y;

	i.image = NULL;
	init_img(g, &i, g->win_width, g->win_height);
	y = 0;
	while (y < g->win_height)
	{
		x = 0;
		while (x < g->win_width)
		{
			paint_pixel_in_frame(g, &i, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g->mlx, g->win, i.image, 0, 0);
	mlx_destroy_image(g->mlx, i.image);
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
