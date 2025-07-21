/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:48:39 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 16:37:12 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_s_image(t_image *img)
{
	img->image = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

void	init_s_map(t_map *n_map)
{
	n_map->fd = 0;
	n_map->line_count = 0;
	n_map->height = 0;
	n_map->width = 0;
	n_map->end_map = 0;
	n_map->path = NULL;
	n_map->file = NULL;
}

void	init_s_player(t_player *player)
{
	player->dir = '\0';
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->cam_x = 0.0;
	player->cam_y = 0.0;
	player->s_rotate = 0.0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
	player->has_moved = 0;
}

void	init_s_ray(t_ray *ray)
{
	ray->cam_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->ngd_x = 0;
	ray->ngd_y = 0;
	ray->ncd_x = 0;
	ray->ncd_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	init_s_general(t_general *gen)
{
	gen->mlx = NULL;
	gen->win = NULL;
	gen->win_height = 400;
	gen->win_width = 600;
	init_s_player(&gen->player);
	init_s_textures(&gen->txt);
	gen->map = NULL;
	init_s_map(&gen->s_map);
	init_s_image(&gen->img);
	gen->txt_pixels = NULL;
	gen->text = NULL;
}
