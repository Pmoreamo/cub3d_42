/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:52:59 by pafranco          #+#    #+#             */
/*   Updated: 2025/08/05 19:03:29 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	door_check(t_general *g, time_t timestamp, int x, int y)
{
	if (g->door_state == OPENING && time(0) - timestamp >= 2)
	{
		g->door_state = OPEN;
		g->map[y][x] = '2';
	}
	else if (g->door_state == OPEN && time(0) - timestamp >= 4)
	{
		g->door_state = CLOSING;
		g->map[y][x] = '3';
	}
	else if (g->door_state == CLOSING && time(0) - timestamp >= 6)
	{
		g->door_state = CLOSED;
		g->map[y][x] = '4';
	}
}

void	door_listener(t_general *g, int mode, int new_x, int new_y)
{
	static time_t	timestamp;
	static int		x;
	static int		y;

	if (mode == 1)
	{
		timestamp = time(0);
		x = new_x;
		y = new_y;
		g->map[y][x] = '3';
		g->door_state = OPENING;
		return ;
	}
	else
		door_check(g, timestamp, x, y);
}
