/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:38:00 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/23 11:39:34 by pmorello         ###   ########.fr       */
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

	r = rgb[0]; //primer numero
	g = rgb[1]; //segon numero
	b = rgb[2]; //tercer numero
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	/* agafem el numero (R,G,B) amb 0xff, nomes agafem els ultims 8 bits,
	per asegurar que no sigui major del limit, un cop agafat el 8 bits (255 = 11111111)
	desplaca aquests 16 cops, i aixi els posa primer 
	11111111 = R / 00000000 = G / 00000000 = B.
	Tambe fa que el RGB sigui un INT de 24bits 3 * 8 = 24 
	pel G, ho fa 8 per posar-ho en el segon grup de 8bits, i el tercer no desplaca pq
	es el utlim grup*/
	return (result);
}

int	check_textures(t_general *g, t_text *t)
{
	if (!t->N || !t->S || !t->W | !t->E) //sino detecta texturas, ERROR
		return (error(g->s_map.path, ERR_TEX_MISSING, 1));
	if (!t->floor || !t->ceiling) //sino detecta FLOOR o CEILING, ERROR
		return (error(g->s_map.path, ERR_COLOR_MISSING, -1));
	if (check_file(t->N, 1) == 1 //comprova que el tipus de arxiu sigui .xpm
		|| check_file(t->S, 1) == 1 //arxiu sigui .xpm
		|| check_file(t->W, 1) == 1 //arxiu sigui .xpm
		|| check_file(t->E, 1) == 1 //arxiu sigui xpm
		|| check_rgb(t->floor) == 1 //comprova que el CODI de COLORS estigui dins dels limits ( 0 -> 255)
		|| check_rgb(t->ceiling) == 1) //comprova CODI COLORS
		return (1); //si en algun falla, torna 1 (ERROR)
	t->hex_floor = rgb_to_hex(t->floor); //pasa de RGB a Hexa
	t->hex_ceiling = rgb_to_hex(t->ceiling); //pasa de RGB a Hexa
	return (0);
}
