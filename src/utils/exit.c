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

void	n_exit(t_general *gen, int code)
{
	if (!gen)
		exit(code);
	exit(code);
}

void	clean_exit(t_general *gen, int code)
{
	if (!gen)
		exit(code);
	if (gen->win && gen->mlx)
		mlx_destroy_window(gen->mlx, gen->win);
	if (gen->mlx)
	{
		mlx_destroy_display(gen->mlx);
		mlx_loop_end(gen->mlx);
		free(gen->mlx);
	}
	exit(code);
}

int	quit(t_general *gen)
{
	clean_exit(gen, 0);
	return (0);
}
