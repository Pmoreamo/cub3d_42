/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:42:02 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 11:00:47 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_textures_pixels(t_general *g)
{
	int	i;
	
	if (g->txt_pixels)
		free_tab((void **)g->txt_pixels);
	g->txt_pixels = ft_calloc(g->win_height + 1, sizeof * g->txt_pixels);
	if (!g->txt_pixels)
		clean_exit(g, error(NULL, ERR_TEX_INVALID, 1));
	i = 0;
	while (i < g->win_height)
	{
		g->txt_pixels[i] = ft_calloc(g->win_width + 1, sizeof * g->txt_pixels[i]);
		if (!g->txt_pixels[i])
			clean_exit(g, error(NULL, ERR_MALLOC, 1));
		i++;
	}
}

static void	get_text_index(t_general *g, t_ray *r)
{
	if (r->wall_type == 0)
	{
		if (r->dir_x < 0)
			g->txt.index = 2;
		else
			g->txt.index = 3;
	}
	else
	{
		if (r->dir_y > 0)
			g->txt.index = 1;
		else
			g->txt.index = 0;
	}
}

void	update_textures_pixels(t_general *g, t_text *t, t_ray *r, int x)
{
	int	y;
	int	color;

	get_text_index(g, r);
	t->x = (int)(r->wall_x * t->size);
	if ((r->wall_type == 0 && r->dir_x < 0) || (r->wall_type == 1 && r->dir_y > 0))
		t->x = t->size - t->x - 1;
	t->step = 1.0 * t->size / r->line_height;
	t->pos = (r->draw_start - g->win_height / 2 + r->line_height / 2) * t->step;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		t->y = (int)t->pos & (t->size - 1);
		t->pos += t->step;
		color = g->text[t->index][t->size * t->y + t->x];
		if (t->index == 0 || t->index == 3)
			color = (color >> 1) & 0x7F7F7F;
		if (color > 0)
			g->txt_pixels[y][x] = color;
		y++;
	}
}
