/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:09:00 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/19 16:05:41 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	wall_collision(t_general *gen, double x, double y)
{
	int	i;
	int	j;
	double	padding;

	i = (int)x;
	j = (int)y;
	padding = 0.1;
	if (gen->map[j][(int)(i + padding)] != '0')
		return (1);
	if (gen->map[j][(int)(i - padding)] != '0')
		return (1);
	if (gen->map[(int)(j + padding)][i] != '0')
		return (1);
	if (gen->map[(int)(j - padding)][i] != '0')
		return (1);
	return (1);
}

static int	is_valid_pos_map(t_general *gen, double x, double y)
{
	if (x < 0.25 || x >= gen->s_map.width - 1.25)
		return (1);
	if (y < 0.25 || y >=gen->s_map.height - 0.25)
		return (1);
	return (0);
}

static int	is_valid_pos(t_general *gen, double x, double y)
{
	if (is_valid_pos_map(gen, x, y) == 0)
		return (0);
	if (wall_collision(gen, x, y) == 0)
		return (0);
	return (1);
}

int	validate_move(t_general *gen, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(gen, new_x, gen->player.pos_y) == 0)
	{
		gen->player.pos_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(gen, gen->player.pos_x, new_y) == 0)
	{
		gen->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}
