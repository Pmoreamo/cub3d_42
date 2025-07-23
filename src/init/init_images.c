/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:43:19 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/23 19:09:41 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_img(t_general *g, t_image *i, int width, int height)
{
	init_s_image(i);
	i->image = mlx_new_image(g->mlx, width, height);
	if (i->image == NULL)
		clean_exit(g, error("mlx", ERR_MLX_IMG, 1));
	i->addr = (int *)mlx_get_data_addr(i->image, &i->pixel_bits,
			&i->size_line, &i->endian);
	return ;
}

void	init_textures_img(t_general *g, t_image *i, char *p)
{
	init_s_image(i);
	i->image = mlx_xpm_file_to_image(g->mlx, p, &g->txt.size, &g->txt.size);
	if (i->image == NULL)
		clean_exit(g, error("mlx", ERR_MLX_IMG, 1));
	i->addr = (int *)mlx_get_data_addr(i->image, &i->pixel_bits,
			&i->size_line, &i->endian);
	return ;
}

void	init_mlx(t_general *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		clean_exit(g, error("mlx", ERR_MLX_START, 1));
	g->win = mlx_new_window(g->mlx, g->win_width, g->win_height, "cub3d");
	if (!g->win)
		clean_exit(g, error("mlx", ERR_MLX_WIN, 1));
}
