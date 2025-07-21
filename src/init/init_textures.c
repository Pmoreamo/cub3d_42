/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:47:19 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 18:13:25 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	*save_xpm_to_mem(t_general *gen, char *path)
{
	t_image	tmp;
	int		*ram;
	int		x;
	int		y;

	init_textures_img(gen, &tmp, path);
	ram = ft_calloc(1, sizeof * ram * gen->txt.size * gen->txt.size);
	if (!ram)
		clean_exit(gen, error(NULL, ERR_MALLOC, 1));
	y = 0;
	while (y < gen->txt.size)
	{
		x = 0;
		while (x < gen->txt.size)
		{
			ram[y * gen->txt.size + x] = tmp.addr[y * gen->txt.size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(gen->mlx, tmp.image);
	return (ram);
}

void	init_textures(t_general *gen)
{
	int	i;

	i = 0;
	gen->text = ft_calloc(5, sizeof * gen->text);
	if (!gen->text)
		clean_exit(gen, error(NULL, ERR_MALLOC, 1));
	gen->text[0] = save_xpm_to_mem(gen, gen->txt.N);
	gen->text[1] = save_xpm_to_mem(gen, gen->txt.S);
	gen->text[2] = save_xpm_to_mem(gen, gen->txt.W);
	gen->text[3] = save_xpm_to_mem(gen, gen->txt.E);
}

void	init_s_textures(t_text *txt)
{
	txt->N = NULL;
	txt->S = NULL;
	txt->E = NULL;
	txt->W = NULL;
	txt->floor = 0;
	txt->ceiling = 0;
	txt->hex_floor = 0x0;
	txt->hex_ceiling = 0x0;
	txt->size = 64;
	txt->step = 0.0;
	txt->pos = 0.0;
	txt->x = 0;
	txt->y = 0;
}
