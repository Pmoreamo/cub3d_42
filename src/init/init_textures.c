/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:47:19 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/09 20:54:46 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	*save_xpm_to_mem(t_general *g, char *path)
{
	/*
	*g : punter a la estructura de GENERAL i els seus elements
	*path : la ruta desde on agafem els .xpm
	*/
	
	t_image	tmp;
	int		*ram;
	int		x;
	int		y;

	/*
	tmp, es una variable per poder accedit a IMAGE de manera temporal
	*ram, es un punter darray, aqui guardarem els pixels 
	x, comptador
	y, comptador
	*/

	init_textures_img(g, &tmp, path);
	/* cridem a la funcio init_textures_img, fa una copia del arxiu .xpm
	i el guarda dins de tmp */
	ram = ft_calloc(g->txt.size * g->txt.size, sizeof(int));
	/* RAM, amb la funcio calloc, diem que reservi memoria per cada pixel 
	de la imatge i cada pixel li donem un pes de INT */
	if (!ram)
		clean_exit(g, error(NULL, ERR_MALLOC, 1));
	y = 0;
	while (y < g->txt.size)
	{
		x = 0;
		while (x < g->txt.size)
		{
			/* 
			Com un .xpm es en 2D(x,y) i al pasaro a la memoria es torna
			un array de 1D. 
			
			Fem servir la seguent formula
			
			ARRAY = y * mida_array  + x
			
            EJEMPLO = imagen 10 pixel, 
			si queremos saber qual es el pixel[3][2] en la memoria
			ARRAY = 2 * 10 + 3 = 23, 
			
			Basicament, accedim a la estructura tmp a dins la variable addr
			copiem el pixel[y * size + x]
			dins de RAM(memoria)[y * size + x]
			aixi passem el arxiu .xpm a la memoria del PC, ens sera mes rapid accedir
			a les texturas */
			ram[y * g->txt.size + x] = tmp.addr[y * g->txt.size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(g->mlx, tmp.image);
	/* un cop copiat, destruim la imatge temporal */
	return (ram);
	/* retornem la imatge de la memoria */
}

void	init_textures(t_general *g)
{
	/*
	*g : punter a la estructura GENERAL i els seus elements
	*/
	
	g->text = ft_calloc(5, sizeof(g->text));
	/* A dins de g->text, creem un array i per aquest array
	reservem memora per a 5 elements amb un pes de g->text bytes*/
	if (!g->text)
		clean_exit(g, error(NULL, ERR_MALLOC, 1));
	/* Entrem en el array i diem que vagi guardant els .xpm dins la memoria i 
	a dins del path (txt.N) */
	g->text[0] = save_xpm_to_mem(g, g->txt.N);
	g->text[1] = save_xpm_to_mem(g, g->txt.S);
	g->text[2] = save_xpm_to_mem(g, g->txt.W);
	g->text[3] = save_xpm_to_mem(g, g->txt.E);
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
