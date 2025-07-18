/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:02:55 by marvin            #+#    #+#             */
/*   Updated: 2025/07/02 10:02:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

/* iniciamos los valores de la struct de IMAGEN */
void    init_s_images(t_image *img)
{
    img->image = NULL;
    img->addr = NULL;
    img->pixel_bits = 0;
    img->size_line = 0;
    img->endian = 0;
}

void    init_s_ray(t_ray *ray)
{
    ray->camera_x = 0;
    ray->dir_x = 0;
    ray->dir_y = 0;
    ray->map_x = 0;
    ray->map_y = 0;
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

/*iniciamos los valores de de la struct MAP*/
void    init_s_map(t_map *map)
{
    map->fd = 0;
    map->line_count = 0;
    map->path = NULL;
    map->file = NULL;
    map->height = 0;
    map->width = 0;
    map->end_map = 0;
}

/* iniciamos los valores de la struct de PLAYER*/
void    init_s_player(t_player *player)
{
    player->dir = '\0';
    player->exist = '\0';
    player->dir_x = 0.0;
    player->dir_y = 0.0;
    player->pos_x = 0.0;
    player->pos_y = 0.0;
    player->plane_x = 0.0;
    player->plane_y = 0.0;
    player->s_rotate = 0.0;
    player->move_x = 0;
    player->move_y = 0;
    player->rotate = 0;
}

/* iniciamos los valores de la struct de TEXTURAS*/
void    init_s_textures(t_texture *text)
{
    text->N = NULL;
    text->S = NULL;
    text->W = NULL;
    text->E = NULL;
    text->floor = 0;
    text->ceiling = 0;
    text->hex_floor = 0x0;
    text->hex_ceiling = 0x0;
    text->w_size = 64;
    text->h_size = 64;
    text->pass = 0.0;
    text->pos = 0.0;
    text->x = 0;
    text->y = 0;
}

/* iniciamos los valores de la struct GENERAL */
void    init_s_general(t_general *gen)
{
    
    gen->mlx = NULL;
    gen->win = NULL;
    gen->win_height = 400;
    gen->win_width = 600;
    init_s_player(&gen->player);
    init_s_textures(&gen->text);
    gen->map = NULL;
    init_s_map(&gen->s_map);
    init_s_images(&gen->img);
    gen->text_pixels = NULL;
    gen->textures = NULL;
}