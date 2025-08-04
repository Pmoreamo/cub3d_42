/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_map_borders.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: pmorello <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/18 10:33:54 by pmorello		   #+#	  #+#			  */
/*	 Updated: 2025/07/19 19:33:53 by pmorello		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_top_and_bottom(char **map, int i, int j)
{
	if (!map || !map[i] || !map[i][j])
		return (1); //si no detecta mapa retorn 1
	while (map[i][j] == ' ' || map[i][j] == '\t'
		|| map[i][j] == '\r' || map[i][j] == '\v'
		|| map[i][j] == '\f')
		j++; //salta espais en blanc i passa al seguent char 
	while (map[i][j])
	{
		if (map[i][j] != '1') //si no detecta cap paret
			return (1); //retorna ERROR
		j++; //passa a la seguent columna
	}
	return (0);
}

int	check_sides(t_map *m, char **new_m)
{
	int		i;
	int		j;

	if (check_top_and_bottom(new_m, 0, 0) == 1) //revisa top map
		return (1);
	i = 1;
	while (i < (m->height - 1)) //va pasant de fila
	{
		j = ft_strlen(new_m[i]) - 1; //calcula la ultima linea
		if (new_m[i][j] != '1') //comprova si el ultim char es un 1
			return (1); //ERROR
		i++;
	}
	if (check_top_and_bottom(new_m, i, 0) == 1) //revisa bottom map
		return (1);
	return (0);
}
