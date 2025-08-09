/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:51:49 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/09 13:49:17 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	n_map_lines(t_general *g, char **file, int i)
{
	int	index;
	int	j;

	index = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
			|| file[i][j] == '\v' || file[i][j] == '\f')
			j++; //saltar espais
		if (file[i][j] != '1') //si no comença amb 1, mapa ha acabat
			break ; //para bucle
		i++; //pasar a la seguent linea
	}
	g->s_map.end_map = i; //indicar la ultima fila del mapa
	return (i - index); //retorna N lineas (linea final - linea inicial)
}

static int	fill_map(t_map *map, char **n_map, int index)
{
	int	i;
	int	j;

	map->width = biggest_line(map, index); //width sera igual a la linea mes gran
	i = 0;
	while (i < map->height)
	{
		j = 0;
		n_map[i] = malloc(sizeof(char) * (map->width + 1)); 
		//Reservem memoria per a map->width (amplada del mapa) + 1, elements, cada element tindra un pes en bytes el que ocupa un char
		if (!n_map) //si falla
			return (error(NULL, ERR_MALLOC, -1));
		while (map->file[index][j] && map->file[index][j] != '\n') //mentres no detecti salts de linea
		{
			n_map[i][j] = map->file[index][j]; //copiar el mapa a la MEMORIA
			j++; //pasar de columna
		}
		while (j < map->width) //mentres linea sigui inferior a la linea mes gran
			n_map[i][j++] = '\0'; //omplir de NULLS la resta de CHARS
		i++; //passar a la seguent fila
		index++; //passar a la seguent filla
	}
	n_map[i] = NULL; //marcar NULL al ultim char
	return (0);
}

static int	load_map(t_general *g, char **file, int i)
{
	g->s_map.height = n_map_lines(g, file, i); 
	//la altura sera igual al numero de lineas del mapa
	g->map = malloc(sizeof(char *) * (g->s_map.height + 1)); 
	//reservem memoria per cada linea + 1(NULL)
	if (!g->map) //si falla
		return (error(NULL, ERR_MALLOC, 1));
	if (fill_map(&g->s_map, g->map, i) == 1) //omplim el mapa
		return (1);
	return (0);
}

static void	blank_to_wall(t_general *g)
{
	int	i;
	int	j;

	i = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j] == ' ' || g->map[i][j] == '\t'
			|| g->map[i][j] == '\r'
			|| g->map[i][j] == '\v' || g->map[i][j] == '\f')
			j++; //saltar els espais en blanc
		while (g->map[i][j])
		{
			if (g->map[i][j] == ' ' && j < (int)ft_strlen(g->map[i]) - 1)
				//si hi ha un espai en blanc dins de la linea,  converteix en paret
				g->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	create_map(t_general *g, char **file, int i)
{
	if (load_map(g, file, i) == -1) //cargar el mapa ala memoria
		return (-1);
	blank_to_wall(g);
	return (0);
}
