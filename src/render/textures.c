/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:42:02 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 16:15:24 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_textures_pixels(t_general *gen)
{
	int	i;

	if (gen->txt_pixels)
		free_tab((void **)gen->txt_pixels);
	gen->txt_pixels = ft_calloc(gen->win_height + 1, sizeof * gen->txt_pixels);
	if (!gen->txt_pixels)
		clean_exit(gen, error(NULL, ERR_TEX_INVALID, 1));
	i = 0;
	while (i < gen->win_height)
	{
		gen->txt_pixels[i] = ft_calloc(gen->win_width + 1, sizeof * gen->txt_pixels);
		if (!gen->txt_pixels[i])
			clean_exit(gen, error(NULL, ERR_MALLOC, 1));
		i++;
	}
}

static void	get_text_index(t_general *gen, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			gen->txt.index = 2;
		else
			gen->txt.index = 3;
	}
	else
	{
		if (ray->dir_y > 0)
			gen->txt.index = 1;
		else
			gen->txt.index = 0;
	}
}

void	update_textures_pixels(t_general *gen, t_text *txt, t_ray *ray, int x)
{
	int	y;
	int	color;

	get_text_index(gen, ray);
	txt->x = (int)(ray->wall_x * txt->size);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0))
		txt->x = txt->size - txt->x - 1;
	txt->step = 1.0 * txt->size / ray->line_height;
	txt->pos = (ray->draw_start - gen->win_height / 2 + ray->line_height / 2) * txt->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		txt->y = (int)txt->pos & (txt->size - 1);
		txt->pos += txt->step;
		color = gen->text[txt->index][txt->size * txt->y + txt->x];
		if (txt->index == 0 || txt->index == 3)
			color = (color >> 1) & 0x7F7F7F;
		if (color > 0)
			gen->txt_pixels[y][x] = color;
		y++;
	}
}
