/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:48:39 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 10:41:39 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_s_image(t_image *i)
{
	i->image = NULL;
	i->addr = NULL;
	i->pixel_bits = 0;
	i->size_line = 0;
	i->endian = 0;
}

void	init_s_map(t_map *m)
{
	m->fd = 0;
	m->line_count = 0;
	m->height = 0;
	m->width = 0;
	m->end_map = 0;
	m->path = NULL;
	m->file = NULL;
}

void	init_s_player(t_player *p)
{
	p->dir = '\0';
	p->dir_x = 0.0;
	p->dir_y = 0.0;
	p->pos_x = 0.0;
	p->pos_y = 0.0;
	p->cam_x = 0.0;
	p->cam_y = 0.0;
	p->s_rotate = 0.0;
	p->move_x = 0;
	p->move_y = 0;
	p->rotate = 0;
	p->has_moved = 0;
}

void	init_s_ray(t_ray *r)
{
	r->pixel_pos = 0;
	r->dir_x = 0;
	r->dir_y = 0;
	r->map_x = 0;
	r->map_y = 0;
	r->step_x = 0;
	r->step_y = 0;
	r->ngd_x = 0;
	r->ngd_y = 0;
	r->ncd_x = 0;
	r->ncd_y = 0;
	r->wall_dist = 0;
	r->wall_x = 0;
	r->wall_type = 0;
	r->line_height = 0;
	r->draw_start = 0;
	r->draw_end = 0;
}

void	init_s_general(t_general *g)
{
	g->mlx = NULL;
	g->win = NULL;
	g->win_height = 300;
	g->win_width = 700;
	init_s_player(&g->player);
	init_s_textures(&g->txt);
	g->map = NULL;
	init_s_map(&g->s_map);
	init_s_image(&g->img);
	g->txt_pixels = NULL;
	g->text = NULL;
	g->door_state = CLOSED;
}
