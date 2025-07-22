/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:56:31 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 13:45:25 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	n_exit(t_general *g, int c)
{
	if (!g)
		exit(c);
	exit(c);
}

void	clean_exit(t_general *g, int c)
{
	if (!g)
		exit(c);
	if (g->win && g->mlx)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		mlx_loop_end(g->mlx);
		free(g->mlx);
	}
	exit(c);
}

int	quit(t_general *g)
{
	clean_exit(g, 0);
	return (0);
}
