/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_key_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:49:05 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/02 19:59:58 by tv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_press(int key, t_general *g)
{
	if (key == XK_Escape)
		quit(g); //si detecta ESC, surt del programa
	if (key == XK_Left)
		g->player.rotate -= 1; //si detecta <- resta 1 a la rotacio
	if (key == XK_Right)
		g->player.rotate += 1; //si detecta -> suma 1 a la rotacio
	if (key == XK_w)
		g->player.move_y = 1; //si detecta W suma 1 al eix Y
	if (key == XK_a)
		g->player.move_x = -1; //si detecta A resta 1 al eix X
	if (key == XK_s)
		g->player.move_y = -1; //si detecta S resta 1 al eix Y
	if (key == XK_d)
		g->player.move_x = 1; //si detecta D suma 1 al eix X
	return (0);
}

static int	key_release(int key, t_general *g)
{
	//atura els moviments
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

static void	mouse_pos(t_general *g, int x, int y)
{
	if (x > g->win_width - 10)
	{
		x = g->win_width - 10;
		mlx_mouse_move(g->mlx, g->win, x, y);
	}
	if (x < 10)
	{
		x = 10;
		mlx_mouse_move(g->mlx, g->win, x, y);
	}
}

static int	mouse_handler(int x, int y, t_general *g)
{
	static int	oldx;
	
	if (x == 0)
		return (0);
	mouse_pos(g, x, y);
	if (x < oldx)
		g->player.has_moved += player_rotate(g, -2);
	else if (x > oldx)
		g->player.has_moved += player_rotate(g, 2);
	oldx = x;
	return (0);
}

void	init_input_keys(t_general *g)
{
	/*adjunta les funcions amb el loop*/
	mlx_hook(g->win, ClientMessage, NoEventMask, quit, g);
	mlx_hook(g->win, KeyPress, KeyPressMask, key_press, g);
	mlx_hook(g->win, KeyRelease, KeyReleaseMask, key_release, g);
	mlx_hook(g->win, MotionNotify, PointerMotionMask, mouse_handler, g);
}
