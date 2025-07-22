/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:06:07 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 17:49:31 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	move_forward(t_general *g)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x + g->player.dir_x * 0.0025;
	new_y = g->player.pos_y + g->player.dir_y * 0.0025;
	return (validate_move(g, new_x, new_y));
}

static int	move_backward(t_general *g)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x - g->player.dir_x * 0.0025;
	new_y = g->player.pos_y - g->player.dir_y * 0.0025;
	return (validate_move(g, new_x, new_y));
}

static int	move_right(t_general *g)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x - g->player.dir_x * 0.0025;
	new_y = g->player.pos_y + g->player.dir_y * 0.0025;
	return (validate_move(g, new_x, new_y));
}

static int	move_left(t_general *g)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x + g->player.dir_x * 0.0025;
	new_y = g->player.pos_y - g->player.dir_y * 0.0025;
	return (validate_move(g, new_x, new_y));
}

int	move_player(t_general *g)
{
	int	moved;

	moved = 0;
	if (g->player.move_y == 1)
		moved += move_forward(g);
	if (g->player.move_y == -1)
		moved += move_backward(g);
	if (g->player.move_x == -1)
		moved += move_left(g);
	if (g->player.move_x == 1)
		moved += move_right(g);
	if (g->player.rotate != 0)
		moved += player_rotate(g, g->player.rotate);
	return (moved);
}
