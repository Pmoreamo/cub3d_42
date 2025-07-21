/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:43:19 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 18:12:51 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_img(t_general *gen, t_image *img, int width, int height)
{
	init_s_image(img);
	img->image = mlx_new_image(gen->mlx, width, height);
	if (img->image == NULL)
		clean_exit(gen, error("mlx", ERR_MLX_IMG, 1));
	img->addr = (int *)mlx_get_data_addr(img->image, &img->pixel_bits,
			&img->size_line, &img->endian);
	return ;
}

void	init_textures_img(t_general *g, t_image *img, char *p)
{
	init_s_image(img);
	img->image = mlx_xpm_file_to_image(g->mlx, p, &g->txt.size, &g->txt.size);
	if (img->image == NULL)
		clean_exit(g, error("mlx", ERR_MLX_IMG, 1));
	img->addr = (int *)mlx_get_data_addr(img->image, &img->pixel_bits,
			&img->size_line, &img->endian);
	return ;
}

void	init_mlx(t_general *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		clean_exit(g, error("mlx", ERR_MLX_START, 1));
	g->win = mlx_new_window(g->mlx, g->win_height, g->win_width, "cub3d");
	if (!g->win)
		clean_exit(g, error("mlx", ERR_MLX_WIN, 1));
}
