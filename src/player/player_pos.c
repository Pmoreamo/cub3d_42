/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerayer_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:13:16 by marvin            #+#    #+#             */
/*   Updated: 2025/07/09 16:59:33 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

static int	is_pos_wall_collision(t_general *gen, double x, double y)
{
	int		i;
	int		j;

	i = (int)x;
	j = (int)y;
	if (gen->map[j][i] == '0')
		return (0);
	return (1);
}

static int	is_valid_pos_map(t_general *gen, double x, double y)
{
	if (x < 0.25 || x >= gen->s_map.width - 1.25)
		return (1);
	if (y < 0.25 || y >= gen->s_map.height - 0.25)
		return (1);
	return (0);
}

static int	is_valid_pos(t_general *gen, double x, double y)
{
	if (is_valid_pos_map(gen, x, y) == 0)
		return (0);
	if (is_pos_wall_collision(gen, x, y) == 0)
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