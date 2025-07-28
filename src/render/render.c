/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:41 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/23 19:42:12 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_color_pixel(t_image *i, int x, int y, int color)
{
	int		pixel;

	pixel = y * (i->size_line / 4) + x;
	/* size_line es el tamany en bytes, per saber el tamany en pixels dividm entre 4 (1pixel son 4 bytes)
	400bytes / 4 == 100pixels, multpliquem per Y i sumen X, per saber la coordenada exacta*/
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
	if (BONUS)
		render_mmap(g);
}

int	render(t_general *g)
{
	g->player.has_moved += move_player(g);
	if (g->player.has_moved == 0)
		return (0);
	render_images(g);
	return (0);
}
