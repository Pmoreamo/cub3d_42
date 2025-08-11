/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:58:50 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 16:29:53 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_raycasting(t_general *g, int x, t_ray *r, t_player *p)
{
	init_s_ray(r);
	r->pixel_pos = 2 * x / (double)g->win_width - 1;
	r->dir_x = p->dir_x + p->cam_x * r->pixel_pos;
	r->dir_y = p->dir_y + p->cam_y * r->pixel_pos;
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;
	r->ncd_x = fabs(1 / r->dir_x);
	r->ncd_y = fabs(1 / r->dir_y);
}

static void	set_ray_dir(t_ray *r, t_player *p)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->ngd_x = (p->pos_x - r->map_x) * r->ncd_x;
	}
	else
	{
		r->step_x = 1;
		r->ngd_x = (r->map_x + 1.0 - p->pos_x) * r->ncd_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->ngd_y = (p->pos_y - r->map_y) * r->ncd_y;
	}
	else
	{
		r->step_y = 1;
		r->ngd_y = (r->map_y + 1.0 - p->pos_y) * r->ncd_y;
	}
}

static void	ray_start_moving(t_general *g, t_ray *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->ngd_x < r->ngd_y)
		{
			r->ngd_x += r->ncd_x;
			r->map_x += r->step_x;
			r->wall_type = 0;
		}
		else
		{
			r->ngd_y += r->ncd_y;
			r->map_y += r->step_y;
			r->wall_type = 1;
		}
		if (r->map_y < 0.25 || r->map_x < 0.25
			|| r->map_y > g->s_map.height - 0.25
			|| r->map_x > g->s_map.width - 1.25)
			break ;
		hit = (g->map[(int)r->map_y][(int)r->map_x]) - '0';
	}
}

static void	cal_line_height(t_ray *r, t_general *g, t_player *p)
{
	if (r->wall_type == 0)
		r->wall_dist = r->ngd_x - r->ncd_x;
	else
		r->wall_dist = (r->ngd_y - r->ncd_y);
	r->line_height = (int)(g->win_height / r->wall_dist);
	r->draw_start = (g->win_height / 2) - (r->line_height) / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + g->win_height / 2;
	if (r->draw_end >= g->win_height)
		r->draw_end = g->win_height - 1;
	if (r->wall_type == 0)
		r->wall_x = p->pos_y + r->wall_dist * r->dir_y;
	else
		r->wall_x = p->pos_x + r->wall_dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);
}

int	raycasting(t_general *g, t_player *p)
{
	t_ray	r;
	int		x;

	x = 0;
	r = g->ray;
	while (x < g->win_width)
	{
		init_raycasting(g, x, &r, p);
		set_ray_dir(&r, p);
		ray_start_moving(g, &r);
		cal_line_height(&r, g, p);
		update_textures_pixels(g, &g->txt, &r, x);
		x++;
	}
	return (0);
}
