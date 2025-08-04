/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:19:27 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/04 18:13:33 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*get_path_textures(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++; //saltar els espais en blanc
	len = j; //començar a on troba el primer caracter
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++; //sumar mentres no siguin espais en blanc
	path = malloc(sizeof(char) * (len - j + 1)); 
	//reservar memoria de tants bytes com chars tingui len - j (espais en blanc) + 1(NULL)
	if (!path) //si falla
		return (NULL); //tornar NULL
	i = 0; 
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++]; //guardar line a path, copiar el path de arxiu a la memoria
	path[i] = '\0'; //NULL
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++; //continuar a la linea
	if (line[j] && line[j] != '\n') //si despre de copiat linea a PATH, detecta mes coses que no sigui un salt de linea
	{
		free(path); //alliberar el path
		path = NULL; //tornarlo com NULL
	}
	return (path); //tornar PATH
}

static int	fill_direction_textures(t_text *t, char *line, int j)
{
	if (line[j] == 'N' && line[j + 1] == 'O' && !(t->N)) 
	//si el char J de la line es N i el seguent char es O i no hi ha textura a N
		t->N = get_path_textures(line, j + 2); //guardar el path a t'->N
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(t->S))
	//lo mateix pero a S
		t->S = get_path_textures(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(t->W))
	//lo mateix pero a W
		t->W = get_path_textures(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(t->E))
	//lo mateix per a E
		t->E = get_path_textures(line, j + 2);
	else
		return (2);
	return (0);
}

static int	get_info_map(t_general *g, char **m, int i, int j)
{
	while (m[i][j] == ' ' || m[i][j] == '\t' || m[i][j] == '\n')
		j++; //mentres hi hagui espais, ves pasant al seguent CHAR
	if (ft_isprint(m[i][j]) && !ft_isdigit(m[i][j])) // si el char es PRINTABLE i NO ES NUMERO
	{
		if (m[i][j] == 'F' || m[i][j] == 'C') //si el char es F o C
		{
			if (fill_color_textures(g, &g->txt, m[i], j) == 2) //cridar funcio COLOR TEXTURAS
				return (1);
			return (3); //tancar el bucle
		}
		else
		{
			if (fill_direction_textures(&g->txt, m[i], j) == 2) //cridar funcio DIRECCIO TEXTURAS
				return (error(g->s_map.path, ERR_TEX_INVALID, 1));
			return (3); //tancar el BUCLE
		}
	}
	else if (ft_isdigit(m[i][j])) //si es un NUMERO
	{
		if (create_map(g, m, i) == 1) //cridar a CREAR MAPA
			return (error(g->s_map.path, ERR_INVALID_MAP, 1));
		return (0); //tornar OK
	}
	return (4); //continuar bucle
}

int	get_file_info(t_general *g, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = get_info_map(g, map, i, j); //cridar a la funcio
			if (ret == 3) //si es 3
				break ; //parar el bucle
			else if (ret == 1)
				return (1); //tornar ERROR
			else if (ret == 0)
				return (0); //tornar SUCCES
			j++; //pasar al seguent columna (lletra/num/...)
		}
		i++; //saltar seguent linea
	}
	return (0);
}
