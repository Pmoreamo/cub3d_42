/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:49:05 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 17:48:46 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_press(int key, t_general *gen)
{
	if (key == XK_Escape)
		quit(gen);
	if (key == XK_Left)
		gen->player.rotate -= 1;
	if (key == XK_Right)
		gen->player.rotate += 1;
	if (key == XK_w)
		gen->player.move_y = 1;
	if (key == XK_a)
		gen->player.move_x = -1;
	if (key == XK_s)
		gen->player.move_y = -1;
	if (key == XK_d)
		gen->player.move_x = 1;
	return (0);
}

static int	key_release(int key, t_general *gen)
{
	if (key == XK_Escape)
		quit(gen);
	if (key == XK_w && gen->player.move_y == 1)
		gen->player.move_y = 0;
	if (key == XK_s && gen->player.move_y == -1)
		gen->player.move_y = 0;
	if (key == XK_a && gen->player.move_x == -1)
		gen->player.move_x += 1;
	if (key == XK_d && gen->player.move_x == 1)
		gen->player.move_x -= 1;
	if (key == XK_Left && gen->player.rotate <= 1)
		gen->player.rotate = 0;
	if (key == XK_Right && gen->player.rotate >= -1)
		gen->player.rotate = 0;
	return (0);
}

void	init_input_keys(t_general *gen)
{
	mlx_hook(gen->win, ClientMessage, NoEventMask, quit, gen);
	mlx_hook(gen->win, KeyPress, KeyPressMask, key_press, gen);
	mlx_hook(gen->win, KeyRelease, KeyReleaseMask, key_release, gen);
}
