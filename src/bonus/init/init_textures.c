/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:47:19 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/04 20:50:01 by pafranco         ###   ########.fr       */
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
	ram = ft_calloc(1, sizeof * ram * g->txt.size * g->txt.size);
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
	//int	i;

	//i = 0;
	g->text = ft_calloc(8, sizeof * g->text);
	if (!g->text)
		clean_exit(g, error(NULL, ERR_MALLOC, 1));
	g->text[0] = save_xpm_to_mem(g, g->txt.N);
	g->text[1] = save_xpm_to_mem(g, g->txt.S);
	g->text[2] = save_xpm_to_mem(g, g->txt.W);
	g->text[3] = save_xpm_to_mem(g, g->txt.E);
	g->text[4] = save_xpm_to_mem(g, g->txt.D[0]);
	g->text[5] = save_xpm_to_mem(g, g->txt.D[1]);
	g->text[6] = save_xpm_to_mem(g, g->txt.D[2]);
}

void	init_s_textures(t_text *t)
{
	t->N = NULL;
	t->S = NULL;
	t->E = NULL;
	t->W = NULL;
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
