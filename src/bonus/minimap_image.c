/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:55:10 by marvin            #+#    #+#             */
/*   Updated: 2025/08/11 14:06:51 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_mmp_tile_pixels(t_mmap *mmp, t_image *img, int *xy, int color)
{
	int		i;
	int		j;

	i = 0;
	while (i < mmp->tile_size)
	{
		j = 0;
		while (j < mmp->tile_size)
		{
			set_color_pixel(img, xy[0] + j, i + xy[1], color);
			j++;
		}
		i++;
	}
}

static void	draw_mmp_tile(t_mmap *mmp, t_image *i, int x, int y)
{
	int		xy[2];

	xy[0] = x * mmp->tile_size;
	xy[1] = y * mmp->tile_size;
	if (mmp->map[y][x] == 'P')
		set_mmp_tile_pixels(mmp, i, xy, 0x00FF00);
	else if (mmp->map[y][x] == '1')
		set_mmp_tile_pixels(mmp, i, xy, 0x808080);
	else if (mmp->map[y][x] == '0')
		set_mmp_tile_pixels(mmp, i, xy, 0xE6E6E6);
	else if (mmp->map[y][x] == ' ')
		set_mmp_tile_pixels(mmp, i, xy, 0x404040);
	else
		set_mmp_tile_pixels(mmp, i, xy, 0x0000FF);
}

static void	set_mmp_border(t_mmap *mmp, int color, t_image *i)
{
	int		size;
	int		x;
	int		y;

	size = MMP_SIZE + mmp->tile_size;
	y = 0;
	while (y <= size + 5)
	{
		x = 0;
		while (x <= size + 5)
		{
			if (x >= size || y >= size)
				set_color_pixel(i, x, y, color);
			else
				set_color_pixel(i, x, y, 0x808080);
			x++;
		}
		y++;
	}
}

static void	draw_mmp(t_mmap *mmp, t_image *i)
{
	int		x;
	int		y;

	y = 0;
	set_mmp_border(mmp, 0x404040, i);
	while (y < mmp->size)
	{
		x = 0;
		while (x < mmp->size)
		{
			if (!mmp->map[y] || mmp->map[y][x] == '\0')
				break ;
			draw_mmp_tile(mmp, i, x, y);
			x++;
		}
		y++;
	}
}

void	minimap_image(t_general *g, t_mmap *mmp, t_image *i)
{
	if (g == 0)
		exit(0);
	draw_mmp(mmp, i);
}
