/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:59:51 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/18 11:05:20 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void		player_n_s(t_player *player)
{
	if (player->dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->cam_x = -0.66;
		player->cam_y = 0;
	}
	if (player->dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->cam_x = 0.66;
		player->cam_y = 0;
	}
}

static void		player_e_w(t_player *player)
{
	if (player->dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->cam_x = 0;
		player->cam_y = -0.66;
	}
	if (player->dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->cam_x = 0;
		player->cam_y = 0.66;
	}
}

void	init_player_dir(t_general *gen)
{
	player_n_s(&gen->player);
	player_e_w(&gen->player);
}

