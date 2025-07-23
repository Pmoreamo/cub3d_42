/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:42:02 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/23 19:40:37 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_textures_pixels(t_general *g)
{
	int	i;
	
	if (g->txt_pixels)
		free_tab((void **)g->txt_pixels);
	/* si ja hi han textures, allibera la taula */
	g->txt_pixels = ft_calloc(g->win_height + 1, sizeof * g->txt_pixels);
	/* reservem memoria per g->win_height elements + 1 amb pes de g->txt_pixels bytes*/
	if (!g->txt_pixels)
		clean_exit(g, error(NULL, ERR_TEX_INVALID, 1));
	/* si fall error */
	i = 0;
	while (i < g->win_height)
	{
		g->txt_pixels[i] = ft_calloc(g->win_width + 1, sizeof * g->txt_pixels[i]);
		/* per element anterior, reservem memoria en cada un de g->win_width elements  + 1 amb un pes de g->txt_pixels[i] bytes*/
		if (!g->txt_pixels[i])
			clean_exit(g, error(NULL, ERR_MALLOC, 1));
		/* pasem al seguent txt_pixel */
		i++;
	}
}

static void	get_text_index(t_general *g, t_ray *r)
{
	if (r->side == 0)
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
	/* per saber quina textura hem de agafar */
	t->x = (int)(r->wall_x * t->size);
	/* desde quin punt hem de dibuixar la textura, agafem el punt on impacta el raig * la mida */
	if ((r->side == 0 && r->dir_x < 0) || (r->side == 1 && r->dir_y > 0))
	/* depenen de si es vertical o horitzontal, el punt inicial sera diferent*/
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
