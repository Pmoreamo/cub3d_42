/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:58:50 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/23 19:31:24 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_raycasting(int x, t_ray *r, t_player *p)
{
	init_s_ray(r);
	r->cam_x = 2 * x / (double)600 - 1;
	/* 	x, es la posicio horitzontal de un pixel, va de 0 a 599, en aquest cas, pq width es 600
	farem 2 * la posicio del pixel/ 600 - 1, aixo es donara un valor que marca si el pixel esta
	esquerra(-1) o dreta (+1) o centre (0)	*/
	r->dir_x = p->dir_x + p->cam_x * r->cam_x; 
	/*	p->dir, indica en quina direcio esta mirant el jugador
	p->cam, forma un vector perpendicular a la dir del jugador, es a dir
	si el jugador te dir x = 1, y = 0, esta mirant a la dreta,
	el seu vector sera x = 0, y = 1, esta mirant cap amunt, aixo
	ens ajuda a saber en quina amplitud estem mirant
	r->cam, ens ajuda a marcar a on esta el pixel per tirar el raig,
	tot junt ens dona la dirrecio a on anira el raig*/
	r->dir_y = p->dir_y + p->cam_y * r->cam_x;
	r->map_x = (int)p->pos_x; //posicio inicial del raig, que es la mateixa que el jugador
	r->map_y = (int)p->pos_y;
	r->ncd_x = fabs(1 / r->dir_x); 
	/*
	distancia a recorre per avacar de cela, segos la dirrecio del raig
	es fa servir fabs, pq sigui un valor positiu
	*/
	r->ncd_y = fabs(1 / r->dir_y);
}

static void	init_ray_in_cell(t_ray *r, t_player *p)
{
	if (r->dir_x < 0) //si la dir es negatiu
	{
		r->step_x = -1; //es moura en dir negativa
		r->ngd_x = (p->pos_x - r->map_x) * r->ncd_x;
		/*
		distancia del jugador fins a la seguent grid, que sera una paret.
		sera la posicio del jugador actual - posicio del raig inicial
		* la distancia recorreguda en las celas
		EX, pos_x = 4.3 / map_x = 4, anem a lesquerra
		4.3 - 4 = -0.3, dinstancia cap a lesquerra fins el seguent grid
		*/
	}
	else
	{
		r->step_x = 1; //es moura en positiu
		r->ngd_x = (r->map_x + 1.0 - p->pos_x) * r->ncd_x;
		/*
		sera la posicio del raig + 1, sera la seguent pos - la posicio del jugador
		aixo es diu quant ens hem mogut * la distancia a recorre entre celas
		EX, pos_x = 4.3 / map_x = 4, si anm a la dreta, sumem 1,
		5 - 4,3 = 0,7, la distancia fins a la seguent grid
		*/
	}
	if (r->dir_y < 0) /*el matix en el eix Y*/
	{
		r->step_y = -1;
		r->ngd_y = (p->pos_y - r->map_y) * r->ncd_y;
	}
	else
	{
		r->step_y = 1;
		r->ngd_y = (r->map_y + 1.0 - p->pos_y) * r->ncd_y;
	}
}

static void	ray_start_moving(t_general *gen, t_ray *r)
{
	int	hit;

	hit = 0;
	while (hit == 0) //mentres no xoqui
	{
		if (r->ngd_x < r->ngd_y)
		/* si la direcio de x es menor a y, 
		es a dir xoca amb una linea horitzontal*/
		{
			r->ngd_x += r->ncd_x;
			/* la distnancia del raig fins al seguent grid*/
			r->map_x += r->step_x;
			/* la posicio de raig x acumulacio de les pases*/
			r->side = 0;
			//el raig ha tocar una cela en X, vertical vist desde adalt
		}
		else
		{
			r->ngd_y += r->ncd_y;
			r->map_y += r->step_y;
			r->side = 1;
			//el raig ha tocat una cela en X, horitzontal vist desde adalt
		}
		if (r->map_y < 0.25 || r->map_x < 0.25
			|| r->map_y > gen->s_map.height - 0.25
			|| r->map_x > gen->s_map.width - 1.25)
			/* limita el raig, pq no surti fora del mapa*/
			break ;
		else if (gen->map[(int)r->map_y][(int)r->map_x] > '0')
		/* si toca una paret*/
			hit = 1; //ha impactat
	}
}

static void	cal_line_height(t_ray *r, t_general *gen, t_player *p)
{
	if (r->side == 0) //si la cela es vertical vist desde adalt
		r->wall_dist = r->ngd_x - r->ncd_x;
		/* 
		si el raig ha creuat una cela X. agafem ngd_x i restem ncd
		pq ja haviem sumat els dos anteriorment 
		*/
	else
		r->wall_dist = (r->ngd_y - r->ncd_y);
		/* a la inversa*/
	r->line_height = (int)(gen->win_height / r->wall_dist);
	/* llargada de la linea = alcada de la paret a dibuiar 
	com mes baixa la linea, mes aprop esta la paret, mes gran sera*/
	r->draw_start = -(r->line_height) / 2 + gen->win_height / 2;
	/* comencem a dibuixar la paret
	suposem que tenim la win de 600pixels, per comencar a dibuixar la paret
	de manera que quedi alineat amb les altres, farem
	la alcada de la paret a dibuixar / 2, per saber el centre del dibuix
	la alcada de win / 2, per saner el centre de la finestra
	600 / 2 = 300 centre de la pantalla
	la paret fa 300pixels 300 / 2 = 150pixels
	300 - 150 = 150, la paret comencara a dibuixarse al pixel 150 de la finestra,
	quan arribi al pixel 300,sera la meitat de la pared
	la alcada del dibuix potser negatiu, ja que en cas 
	de que el dibuix sigui mes gran que la pantallapot evitar 
	glitchs visuals*/
	if (r->draw_start < 0)
		r->draw_start = 0;
	/* si el dibuix es negatiu, liniciem a 0, aixi nomes
	es dibuixa dins la linea*/
	r->draw_end = r->line_height / 2 + gen->win_height / 2;
	/* la meitat del dibuix es pint a la segona part de win_height
	sera fins el pixel 450*/
	if (r->draw_end >= gen->win_height)
		r->draw_end = gen->win_height - 1;
	/* aixo assegura que la part inferior del dibuix, no passi
	la finestra
	EX:	si el draw_end = 650, pero la finestra = 600
	cal tallar el dibuix a 599*/
	if (r->side == 0)
		r->wall_x = p->pos_y + r->wall_dist * r->dir_y;
		/* si la paret es vertical, per calcular el punt on impacta
		el raig, hem de fer servir el eix vertical Y*/
	else
		r->wall_x = p->pos_x + r->wall_dist * r->dir_x;
		/*si la paret es horitzontal, per calcular el punt on impacta
		el rai, hem de fer servir el eix horitzontal X*/
	r->wall_x -= floor(r->wall_x);
	/* aixo trasnforma el punt de impacte en fraccio, per ser mes precis
	EX: si el raig xoca a x = 2,7 dins la cela
	wall_x = 0,7 i nomes mostrarem el 70% de la textura horitzontal*/
}

int	raycasting(t_general *gen, t_player *p)
{
	t_ray	r;
	int		x;

	x = 0;
	r = gen->ray;
	while (x < gen->win_width)
	{
		init_raycasting(x, &r, p);
		init_ray_in_cell(&r, p);
		ray_start_moving(gen, &r);
		cal_line_height(&r, gen, p);
		update_textures_pixels(gen, &gen->txt, &r, x);
		x++;
	}
	return (0);
}
