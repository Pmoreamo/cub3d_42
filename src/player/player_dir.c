/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:59:51 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 10:57:12 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	player_n_s(t_player *p)
{
	if (p->dir == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->cam_x = -0.66;
		p->cam_y = 0;
	}
	if (p->dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->cam_x = 0.66;
		p->cam_y = 0;
	}
}

static void	player_e_w(t_player *p)
{
	if (p->dir == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->cam_x = 0;
		p->cam_y = -0.66;
	}
	if (p->dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->cam_x = 0;
		p->cam_y = 0.66;
	}
}

void	init_player_dir(t_general *g)
{
	player_n_s(&g->player);
	player_e_w(&g->player);
}
