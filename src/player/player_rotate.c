/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:49:49 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 13:16:09 by tv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	rotation(t_general *g, double speed)
{
	t_player	*p;
	double		tmp_x;
	
	p = &g->player; 
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
	p->dir_y = tmp_x * sin(speed) + p->dir_y * cos(speed);
	tmp_x = p->cam_x;
	p->cam_x = p->cam_x * cos(speed) - p->cam_y * sin(speed);
	p->cam_y = tmp_x * sin(speed) + p->cam_y * cos(speed);
	return (1);
}

int	player_rotate(t_general *g, double dir)
{
	int		moved;
	double	speed;

	moved = 0;
	speed = 0.015 * dir;
	moved += rotation(g, speed);
	return (moved);
}
