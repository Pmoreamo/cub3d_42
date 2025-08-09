/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:58:50 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/09 18:56:14 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_raycasting(int x, t_ray *r, t_player *p)
{
	init_s_ray(r);
	r->cam_x = 2 * x / (double)600 - 1;
	/* 
	cam_x : indica la posicio horitzontal de un pixel. 
	Al saber la posicio del pixel, podem saber en quina direcio anira el raig. 
	La posicio esta marcat per un rang de -1 a 1 (-1, 0, 1)
	*/

	r->dir_x = p->dir_x + p->cam_x * r->cam_x; 
	r->dir_y = p->dir_y + p->cam_y * r->cam_x;
	/*
	r->dir : indica la direccio del raig.
	direccio del jugador (p->dir), a on mira
	+ 
	el camp de visio que te el jugador (p->cam), que hi ha dins la vista del jugador
	* 
	la posicio del pixel a on volem anar (cam_x)
	*/
	
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;
	/*
	map_x : indica en quina posicio esta el raig, com va cela per cela, per comprovar
	quina es una paret (1)	
	*/

	r->ncd_x = fabs(1 / r->dir_x); 
	r->ncd_y = fabs(1 / r->dir_y);
	/*
	r->ncd : indica la distancia que recorre un raig dins de UNA cela del mapa
	Quina direccio es mou (r->dir), cap a on esta anant
	1, es la mida de a cela. 
	fem servir la funcio fabs, pq el valor ens doni positiu, 
	ja que la distancia recorreguda sempre sera +, independenment de la dir

	EX: 
	Si tenim que el raig va en dir_x = 0,5, 
	la distancia que recorre dins 1 unitat
	1 / 0,5 = 2
	per creuar a la seguent cela, el raig ha de moures 2,
	2 NO SON CELAS, sino que es una manera de marcar que el moviment sera mes llarg
	*/
	
}

static void	set_ray_dir(t_ray *r, t_player *p)
{
	if (r->dir_x < 0) //Si la dirrecio es menor a 0, es a dir negatiu
	{
		r->step_x = -1; //Avancara esquerra
		r->ngd_x = (p->pos_x - r->map_x) * r->ncd_x;
		/*
		La distancia fins a la proxima linea,
		posicio del jugador(p->pos), on esta el jugador en aquell moment
		-
		on esta el raig en aquell moment(r->pos), en quina casella esta el raig
		*
		distancia que hi ha dins 1 casella (r->ncd)

		EX:
		pos = casella 3.7
		r->map = 3, el raig esta en la casella 3
		com va esquerra hem de restar, el resultat multiplicar per la distancia
		de una cela, per tenir el valor de quant recorrera fins arribar a la seguent linea
		vertical de lesquerra.

		3.7 - 3 = 0.7 * 1 = 0.7, 

		El raig ha de recorrer 0.7 unitats per arribar a la seguent linea
		vertical esquerra del nou grid
		*/
	}
	else
	{
		r->step_x = 1; //Avanca dreta
		r->ngd_x = (r->map_x + 1.0 - p->pos_x) * r->ncd_x;
		/*
		Distancia fins la proxima linea,
		posicio actual del raig (r->map), on esa el raig
		com es mou a la dreta, +1, per indicar que el moviment sera la seguent cela
		-
		posicio del jugador (p->pos), on esta el jugador en aquell moment
		*
		ncd

		EX:
		p->pos = 3.7
		r->map = 3
		com va dreta, sumem + 1, per indicar quina sera 
		la casella desti = r->map + 1 = 4
		per tenir el valor de quant ha de recorrer per arriar a la seguent 
		casella vertical dret

		3 + 1 = 4 - 3.7 = 0.3 * r->ncd = 0.3

		El raig ha de recorrer 0.3 unitats per arribar a la segunet linea vertical
		dret del nou grid
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

static void	ray_start_moving(t_general *g, t_ray *r)
{
	int	hit;

	hit = 0;
	while (hit == 0) //Mentres xoc == 0
	{
		if (r->ngd_x < r->ngd_y)
		/* Si la distancia vertical a recorre es menor a la distancia horitzonal
		es a dir xoca amb una paret que es DRETA o ESQUERRA */
		{
			r->ngd_x += r->ncd_x;
			/* El reocrregut sera igual a la suma de la distancia de les casellas,
			el que falta recorre per arribar a la seguen linea del grid
			EX:
			0.3 < 0.7
			
			ngdc = 0.3 + 1 = 1.3, es a dir per arribar a la seguent casella en X, haura 
			de recorre 1.3 unitats			
			*/
			r->map_x += r->step_x;
			/* Actualitza la posicio del raig, segons quan ha avancat 
			llavors ara tindrem la nova posicio del raig */
			r->wall_type = 0;
			/* com el raig ha tocar una paret en eix X, diem que es una paret que pot
			ser ESQUERRA DRETA */
		}
		else
		{
			r->ngd_y += r->ncd_y;
			r->map_y += r->step_y;
			r->wall_type = 1;
			//el raig ha tocat una cela en Y, es  a dir si es ADALT o ABAIX
		}
		if (r->map_y < 0.25 || r->map_x < 0.25
			|| r->map_y > g->s_map.height - 0.25
			|| r->map_x > g->s_map.width - 1.25)
			/* Si la posicio del raig es inferior a 0.25 en els eixos X, Y
			o es superior a la aclada de la finestra - 0.25 o es superior
			a la amplada de la finestra - 1.25) .25, son marges */
			break ; //para el bucle
		else if (g->map[(int)r->map_y][(int)r->map_x] > '0')
		/* Si la posicio del raig es superior a 0 */
			hit = 1; //Ha impactat en una paret
	}
}

static void	cal_line_height(t_ray *r, t_general *g, t_player *p)
{
	if (r->wall_type == 0) //
		r->wall_dist = r->ngd_x - r->ncd_x;
		/* Si la paret es 0, vol dir que es una paret esquerra o dreta
		la distancia del raig a la paret = Agafem la distancia que ha recorregut
		el raig per tocar la linea del grid - la distancia que ha recoregut dins la cela.
		EX: 
		p->pos_x = 3.7
		r->map_x = 3
		r->dir_x < 0
		r->ngd_x = p->pos_x - r->map_x * r->ncd_x
		3.7 - 3 = 0.7 * 1 = 0.7
		La distancia a la seguent linea vertical es 0.7
		Movem el raig ncd_x = 0.7 + 1 = 1.7
		1.7 esta dins de una cela, vol dir que ha travesat la linea anterior, per lo 
		tant la distancia real a una paret = ngd_x = ncd_x = 1.7 - 1 = 0.7
		aixi que la distancia a la paret es de 0.7 */
	else
		r->wall_dist = (r->ngd_y - r->ncd_y);
		/* El mateix per amb les parets que son 1 (ADALT, ABAIX) */
	r->line_height = (int)(g->win_height / r->wall_dist);
	/* Calcula la alcada que haura de tenir la paret, segons la distancia
	del raig a la paret  */
	r->draw_start = (g->win_height / 2) - (r->line_height) / 2;
	/* r->draw_start : indica en quin pixel es comencara a dibuixar la paret
	agafem la alcada de la finestra / 2, per saber el punt central de la alcada
	agafem la alcada de la paret / 2, per saber el punt central del dibuix
	Al restar els dos valors, sabem el pixel exacte on comencar a dibuixar la paret
	EX:
	g->win_height = 600 / 2 = 300
	r->line_height = 200 / 2 = 100
	300 - 100 = 200, 
	la paret es comencara a dibuixar en el pixel 200 de la finestra */
	if (r->draw_start < 0)
		r->draw_start = 0;
	/* si el pixel on es comenca a dibuixar es inferior a 0
	direm que comenci a dibuixar en el pixel 0 */
	r->draw_end = r->line_height / 2 + g->win_height / 2;
	/* El matex que draw_start, pero a la part contraria i es per acabar el dibuix */
	if (r->draw_end >= g->win_height)
		r->draw_end = g->win_height - 1;
	/* aixo assegura que la part inferior del dibuix, no passi
	la finestra
	EX:	si el draw_end = 650, pero la finestra = 600
	cal tallar el dibuix a 599*/
	if (r->wall_type == 0)
		r->wall_x = p->pos_y + r->wall_dist * r->dir_y;
	/* Si el tipus de paret es ESQUERRA, DRETA, es a dir si es vertical en el mapa
	calculem r->wall_x, on impacta el raig en la paret
	Com calculem les parets verticals hem de fer servir el eix Y, llavors el punt de impacte
	p->pos, la posicio del jugador
	r->wall_dist, la distancia del raig fins a impactar en una paret
	r->dir, la direccio del raig
	EX:
	posicio = 2
	distancia = 5
	dir = 1
	el punt exacte = 2 + 5 * 1 = 7
	Estem dient que el raig a impactat en la posicio 7 del eix Y de la paret */
	else
		r->wall_x = p->pos_x + r->wall_dist * r->dir_x;
		/*si la paret es horitzontal, per calcular el punt on impacta
		el rai, hem de fer servir el eix horitzontal X*/
	r->wall_x -= floor(r->wall_x);
	/* aixo trasnforma el punt de impacte en fraccio, per ser mes precis
	EX: si el raig xoca a x = 2,7 dins la cela
	wall_x = 0,7 i nomes mostrarem el 70% de la textura horitzontal*/
}

int	raycasting(t_general *g, t_player *p)
{
	t_ray	r;
	int		x;

	x = 0;
	r = g->ray;
	while (x < g->win_width)
	{
		init_raycasting(x, &r, p);
		set_ray_dir(&r, p);
		ray_start_moving(g, &r);
		cal_line_height(&r, g, p);
		update_textures_pixels(g, &g->txt, &r, x);
		x++;
	}
	return (0);
}
