/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:09:00 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/04 21:40:00 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	wall_collision(t_general *g, double x, double y)
{
    // Si alguna *de les posicions properes toca una paret, hi ha col·lisió
    if (g->map[(int)y][(int)x] == '0')
	{
        return (0);
	}
	else if (g->map[(int)y][(int)x] == '4')
	{

	}
    return (1);
}

static int	is_valid_pos_map(t_general *g, double x, double y)
{
	if (x < 0.25 || x >= g->s_map.width - 1.25)
	/* 0.25, pq les coordenades dun mapa son enters, 1,0... 
	pq el jugador es mogui fluidament necesitem valors decimals, 
	llavors 0.25 indica si esta molt aprop del valor X
	- 1.25, es per indicar que el limit abans de la ultima cela
	*/
		return (1);
	if (y < 0.25 || y >= g->s_map.height - 0.25)
		return (1);
	return (0);
}

static int	is_valid_pos(t_general *g, double x, double y)
{
	if (wall_collision(g, x, y) == 1 || is_valid_pos_map(g, x, y) == 1)
		return (0);
	return (1);
}

int	validate_move(t_general *g, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(g, new_x, g->player.pos_y) == 1)
	{
		g->player.pos_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(g, g->player.pos_x, new_y) == 1)
	{
		g->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}
