/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:21:41 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 16:38:13 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_color_pixel(t_image *img, int x, int y, int color)
{
	int	pixel;
	
	pixel = y * (img->size_line / 4) + x;
	img->addr[pixel] = color;
}

void	paint_pixel_in_frame(t_general *gen, t_image *img, int x, int y)
{
	if (gen->txt_pixels[y][x]> 0)
		set_color_pixel(img, x, y, gen->txt_pixels[y][x]);
	else if (y < gen->win_height / 2)
		set_color_pixel(img, x, y, gen->txt.hex_ceiling);
	else if (y < gen->win_height - 1)
		set_color_pixel(img, x, y, gen->txt.hex_floor);
}

static void	put_frame_in_window(t_general *gen)
{
	t_image	img;
	int	x;
	int	y;

	img.image = NULL;
	init_img(gen, &img, gen->win_width, gen->win_height);
	y = 0;
	while ( y < gen->win_height)
	{
		x = 0;
		while (x < gen->win_width)
		{
			paint_pixel_in_frame(gen, &img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(gen->mlx, gen->win, img.image, 0, 0);
	mlx_destroy_image(gen->mlx, img.image);
}

static void	draw_raycast(t_general *gen)
{
	init_textures_pixels(gen);
	init_s_ray(&gen->ray);
	raycasting(gen, &gen->player);
	put_frame_in_window(gen);
}

int	render(t_general *gen)
{
	gen->player.has_moved += move_player(gen);
	if (gen->player.has_moved == 0)
		return (0);
	draw_raycast(gen);
	return (0);
}
