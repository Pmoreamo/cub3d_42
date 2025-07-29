/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:21:46 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/29 17:26:05 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int  mouse_pos(t_general *g, int x, int y)
{
    if (x > g->win - 20)
    {
        x = 20;
        mlx_mouse_move(g->mlx, g->win, x, y);
    }
    if (x < 20)
    {
        x = g->win - 20;
        mlx_mouse_move(g->mlx, g->win, x, y);
    }
}

static int  mouse_handler(int x, int y, t_general *g)
{
    int  old_x = g->win_width / 2;    
}
