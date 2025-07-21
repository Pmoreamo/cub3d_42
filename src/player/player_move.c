/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:06:07 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 14:19:42 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	move_forward(t_general *gen)
{
	double	new_x;
	double	new_y;

	new_x = gen->player.pos_x + gen->player.dir_x * 0.0025;
	new_y = gen->player.pos_y + gen->player.dir_y * 0.0025;
	return (validate_move(gen, new_x, new_y));
}

static int	move_backward(t_general *gen)
{
	double	new_x;
	double	new_y;

	new_x = gen->player.pos_x - gen->player.dir_x * 0.0025;
	new_y = gen->player.pos_y - gen->player.dir_y * 0.0025;
	return (validate_move(gen, new_x, new_y));
}

static int	move_right(t_general *gen)
{
	double	new_x;
	double	new_y;

	new_x = gen->player.pos_x - gen->player.dir_x * 0.0025;
	new_y = gen->player.pos_y + gen->player.dir_y * 0.0025;
	return (validate_move(gen, new_x, new_y));
}

static int	move_left(t_general *gen)
{
	double	new_x;
	double	new_y;

	new_x = gen->player.pos_x + gen->player.dir_x * 0.0025;
	new_y = gen->player.pos_y - gen->player.dir_y * 0.0025;
	return (validate_move(gen, new_x, new_y));
}

int	move_player(t_general *gen)
{
	int	moved;
	
	moved = 0;
	if (gen->player.move_y == 1)
		moved += move_forward(gen);
	if (gen->player.move_y == -1)
		moved += move_backward(gen);
	if (gen->player.move_x == -1)
		moved += move_left(gen);
	if (gen->player.move_x == 1)
		moved += move_right(gen);
	if (gen->player.rotate != 0)
		moved += player_rotate(gen, gen->player.rotate);
	return (moved);
}
