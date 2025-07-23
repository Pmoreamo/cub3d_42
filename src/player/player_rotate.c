/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:49:49 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/23 13:28:02 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	rotation(t_general *g, double speed)
{
	t_player	*p;
	double		tmp_x;
	/*
	x' = x * cos(θ) - y * sin(θ)
	y' = x * sin(θ) + y * cos(θ)
	formula matematica per girar un vector en un angle (0) 
	*/

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

	moved = 0; //no sha mogut
	speed = 0.015 * dir; //velocitat de moviment * direccio
	moved += rotation(g, speed);
	return (moved);
}
