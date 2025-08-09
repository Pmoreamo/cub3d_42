/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:42:02 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/09 21:21:33 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_textures_pixels(t_general *g)
{
	int	i; //comptador 
	
	if (g->txt_pixels)
		free_tab((void **)g->txt_pixels);
	/* si ja hi han textures, allibera la taula */
	g->txt_pixels = ft_calloc(g->win_height + 1, sizeof * g->txt_pixels);
	/* reservem memoria per cada linea de la finestra + 1 
	amb pes de g->txt_pixels bytes */
	if (!g->txt_pixels)
		clean_exit(g, error(NULL, ERR_TEX_INVALID, 1));
	/* si fall error */
	i = 0;
	while (i < g->win_height)
	{
		g->txt_pixels[i] = ft_calloc(g->win_width + 1, sizeof * g->txt_pixels[i]);
		/* A dins de cada linea reservem memoria per cada columne de la finestra + 1
		amb pes de g->txt_pixels bytes */
		if (!g->txt_pixels[i])
			clean_exit(g, error(NULL, ERR_MALLOC, 1));
		/* pasem a la seguent linea*/
		i++;
	}
}

static void	get_text_index(t_general *g, t_ray *r)
{
	if (r->wall_type == 0)
	{
		if (r->dir_x < 0)
			g->txt.index = 2;
		else
			g->txt.index = 3;
	}
	else
	{
		if (r->dir_y > 0)
			g->txt.index = 1;
		else
			g->txt.index = 0;
	}
}

void	update_textures_pixels(t_general *g, t_text *t, t_ray *r, int x)
{
	int	y;
	int	color;

	get_text_index(g, r);
	/* per saber quina textura hem de agafar */
	t->x = (int)(r->wall_x * t->size);
	/* calcula quin pixel x es, basat en el impacte del raig a la paret * la mida */
	if ((r->wall_type == 0 && r->dir_x < 0) || (r->wall_type == 1 && r->dir_y > 0))
	/* Si la paret es VERTICAL i el ragi va a la esquerra o 
	si la paret es HORITZONTAL i el raig va cap avall */
		t->x = t->size - t->x - 1;
	/* el pixel queda invertit de manera que dibuixara la textura "reflexada" */
	t->step = 1.0 * t->size / r->line_height;
	/* calcula quant s’ha de "moure" verticalment la textura per cada pixel 
	que es dibuixa (perquè la textura s’ajusti a l’alçada de la paret en pantalla) */
	t->pos = (r->draw_start - g->win_height / 2 + r->line_height / 2) * t->step;
	/* Ens diu quin a partir de quin pixel vertical hem de comencar a pintar
	la paret en la finestra */
	y = r->draw_start;
	/* marquem que y es la part superior del dibuix */
	while (y < r->draw_end)
	{
		/* mentres es dibuixi la part superior */
		t->y = (int)t->pos & (t->size - 1);
		/* calcular el pixel invertit de y */
		t->pos += t->step;
		/* a partir de quin pixel horitzontal comencar a pintar */
		color = g->text[t->index][t->size * t->y + t->x];
		/* Defineix el color del pixel, 
		primer mirar quin index es, quina textura (N,S,E,O) i despres busca el pixel 
		en el array 1D, per saber el color */
		if (t->index == 0 || t->index == 3)
			color = (color >> 1) & 0x7F7F7F;
		if (color > 0)
			g->txt_pixels[y][x] = color;
		y++;
	}
}
