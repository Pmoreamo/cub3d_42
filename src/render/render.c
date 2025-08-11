/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:41 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 13:16:33 by tv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_color_pixel(t_image *i, int x, int y, int color)
{
	int		pixel;

	pixel = y * (i->size_line / 4) + x;
	i->addr[pixel] = color; 
}

void	paint_pixel_in_frame(t_general *g, t_image *i, int x, int y)
{
	if (g->txt_pixels[y][x] > 0) 
		set_color_pixel(i, x, y, g->txt_pixels[y][x]);
	else if (y < g->win_height / 2) 
		set_color_pixel(i, x, y, g->txt.hex_ceiling);
	else
		set_color_pixel(i, x, y, g->txt.hex_floor); 
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
	static int	move;

	g->player.has_moved += move_player(g);
	if (g->player.has_moved != move)
	{
		move = g->player.has_moved;
		render_images(g);
	}
	return (0);
}
