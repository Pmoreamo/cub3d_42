/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:09:00 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 14:08:53 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	wall_collision(t_general *g, double x, double y)
{
	char		cell;

	cell = g->map[(int)y][(int)x];
	if (cell == '0')
		return (0);
	else if (cell != '1' && g->door_state <= OPEN)
	{
		if (g->door_state == CLOSED)
			door_listener(g, 1, (int)x, (int)y);
		else if (cell == '2')
			return (0);
	}
	return (1);
}

static int	is_valid_pos_map(t_general *g, double x, double y)
{
	if (x < 0.25 || x >= g->s_map.width - 1.25)
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
