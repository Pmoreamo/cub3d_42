/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:38:00 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 12:56:36 by pmorello         ###   ########.fr       */
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

int		check_textures(t_general *gen, t_text *txt)
{
	if (!txt->N || !txt->S || !txt->W | !txt->E)
		return (error(gen->s_map.path, ERR_TEX_MISSING, 1));
	if (!txt->floor || !txt->ceiling)
		return (error(gen->s_map.path, ERR_COLOR_MISSING, -1));
	if (check_file(txt->N, 1) == 1
		|| check_file(txt->S, 1) == 1
		|| check_file(txt->W, 1) == 1
		|| check_file(txt->E, 1) == 1
		|| check_rgb(txt->floor) == 1
		|| check_rgb(txt->ceiling) == 1)
		return (1);
	txt->hex_floor = rgb_to_hex(txt->floor);
	txt->hex_ceiling = rgb_to_hex(txt->ceiling);
	return (0);
}
