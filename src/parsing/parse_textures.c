/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:38:00 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 18:09:23 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_rgb(int *rgb)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (error(NULL, ERR_TEX_RGB_VAL, 1));
		i++;
	}
	return (0);
}

static unsigned long	rgb_to_hex(int *rgb)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int	check_textures(t_general *g, t_text *t)
{
	if (!t->N || !t->S || !t->W | !t->E)
		return (error(g->s_map.path, ERR_TEX_MISSING, 1));
	if (!t->floor || !t->ceiling)
		return (error(g->s_map.path, ERR_COLOR_MISSING, -1));
	if (check_file(t->N, 1) == 1
		|| check_file(t->S, 1) == 1
		|| check_file(t->W, 1) == 1
		|| check_file(t->E, 1) == 1
		|| check_rgb(t->floor) == 1
		|| check_rgb(t->ceiling) == 1)
		return (1);
	t->hex_floor = rgb_to_hex(t->floor);
	t->hex_ceiling = rgb_to_hex(t->ceiling);
	return (0);
}
