/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:47:19 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 13:10:51 by tv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	*save_xpm_to_mem(t_general *g, char *path)
{
	t_image	tmp;
	int		*ram;
	int		x;
	int		y;

	init_textures_img(g, &tmp, path);
	ram = ft_calloc(g->txt.size * g->txt.size, sizeof(int));
	if (!ram)
		clean_exit(g, error(NULL, ERR_MALLOC, 1));
	y = 0;
	while (y < g->txt.size)
	{
		x = 0;
		while (x < g->txt.size)
		{
			ram[y * g->txt.size + x] = tmp.addr[y * g->txt.size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(g->mlx, tmp.image);
	return (ram);
}

void	init_textures(t_general *g)
{
	g->text = ft_calloc(5, sizeof(g->text));
	if (!g->text)
		clean_exit(g, error(NULL, ERR_MALLOC, 1));
	g->text[0] = save_xpm_to_mem(g, g->txt.n);
	g->text[1] = save_xpm_to_mem(g, g->txt.s);
	g->text[2] = save_xpm_to_mem(g, g->txt.w);
	g->text[3] = save_xpm_to_mem(g, g->txt.e);
}

void	init_s_textures(t_text *t)
{
	t->n = NULL;
	t->s = NULL;
	t->e = NULL;
	t->w = NULL;
	t->floor = 0;
	t->ceiling = 0;
	t->hex_floor = 0x0;
	t->hex_ceiling = 0x0;
	t->size = 64;
	t->step = 0.0;
	t->pos = 0.0;
	t->x = 0;
	t->y = 0;
}
