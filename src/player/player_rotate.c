/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:49:49 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 17:56:39 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	rotation(t_general *gen, double speed)
{
	t_player	*p;
	double		tmp_x;

	p = &gen->player;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
	p->dir_y = tmp_x * sin(speed) + p->dir_y * cos(speed);
	tmp_x = p->cam_x;
	p->cam_x = p->cam_x * cos(speed) - p->cam_y * sin(speed);
	p->cam_y = tmp_x * sin(speed) + p->cam_y * cos(speed);
	return (1);
}

int	player_rotate(t_general *gen, double dir)
{
	int		moved;
	double	speed;

	moved = 0;
	speed = 0.0025 * dir;
	moved += rotation(gen, speed);
	return (moved);
}
