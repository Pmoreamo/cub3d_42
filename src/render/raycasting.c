/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:58:50 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 17:40:42 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_raycasting(int x, t_ray *ray, t_player *player)
{
	init_s_ray(ray);
	ray->cam_x = 2 * x / (double)600 - 1;
	ray->dir_x = player->dir_x + player->cam_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->cam_y * ray->cam_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->ncd_x = fabs(1 / ray->dir_x);
	ray->ncd_y = fabs(1 / ray->dir_y);
}

static void	init_ray_in_cell(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->ngd_x = (player->pos_x - ray->map_x) * ray->ncd_x;
	}
	else
	{
		ray->step_x = 1;
		ray->ngd_x = (ray->map_x + 1.0 - player->pos_x) * ray->ncd_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->ngd_y = (player->pos_y - ray->map_y) * ray->ncd_y;
	}
	else
	{
		ray->step_y = 1;
		ray->ngd_y = (ray->map_y + 1.0 - player->pos_y) * ray->ncd_y;
	}
}

static void	ray_start_moving(t_general *gen, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->ngd_x < ray->ngd_y)
		{
			ray->ngd_x += ray->ncd_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->ngd_y += ray->ncd_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25 || ray->map_x < 0.25
			|| ray->map_y > gen->s_map.height - 0.25
			|| ray->map_x > gen->s_map.width - 1.25)
			break ;
		else if (gen->map[(int)ray->map_y][(int)ray->map_x] > '0')
			hit = 1;
	}
}

static void	cal_line_height(t_ray *ray, t_general *gen, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = ray->ngd_x - ray->ncd_x;
	else
		ray->wall_dist = (ray->ngd_y - ray->ncd_y);
	ray->line_height = (int)(gen->win_height / ray->wall_dist);
	ray->draw_start = (ray->line_height) / 2 + gen->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + gen->win_height / 2;
	if (ray->draw_end >= gen->win_height)
		ray->draw_end = gen->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

int	raycasting(t_general *gen, t_player *player)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = gen->ray;
	while (x < gen->win_width)
	{
		init_raycasting(x, &ray, player);
		init_ray_in_cell(&ray, player);
		ray_start_moving(gen, &ray);
		cal_line_height(&ray, gen, player);
		update_textures_pixels(gen, &gen->txt, &ray, x);
		x++;
	}
	return (0);
}
