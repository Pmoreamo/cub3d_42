/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:49:05 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 10:57:06 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_press(int key, t_general *g)
{
	if (key == XK_Escape)
		quit(g);
	if (key == XK_Left)
		g->player.rotate -= 1;
	if (key == XK_Right)
		g->player.rotate += 1;
	if (key == XK_w)
		g->player.move_y = 1;
	if (key == XK_a)
		g->player.move_x = -1;
	if (key == XK_s)
		g->player.move_y = -1;
	if (key == XK_d)
		g->player.move_x = 1;
	return (0);
}

static int	key_release(int key, t_general *g)
{
	if (key == XK_Escape)
		quit(g);
	if (key == XK_w && g->player.move_y == 1)
		g->player.move_y = 0;
	if (key == XK_s && g->player.move_y == -1)
		g->player.move_y = 0;
	if (key == XK_a && g->player.move_x == -1)
		g->player.move_x = 0;
	if (key == XK_d && g->player.move_x == 1)
		g->player.move_x = 0;
	if (key == XK_Left && g->player.rotate <= 1)
		g->player.rotate = 0;
	if (key == XK_Right && g->player.rotate >= -1)
		g->player.rotate = 0;
	return (0);
}

void	init_input_keys(t_general *g)
{
	mlx_hook(g->win, ClientMessage, NoEventMask, quit, g);
	mlx_hook(g->win, KeyPress, KeyPressMask, key_press, g);
	mlx_hook(g->win, KeyRelease, KeyReleaseMask, key_release, g);
}
