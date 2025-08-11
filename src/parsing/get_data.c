/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:19:27 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 10:48:07 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*get_path_textures(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1)); 
	if (!path)
		return (NULL);
	i = 0; 
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	fill_direction_textures(t_text *t, char *line, int j)
{
	if (line[j] == 'N' && line[j + 1] == 'O' && !(t->n)) 
	//si el char J de la line es N i el seguent char es O i no hi ha textura a N
		t->n = get_path_textures(line, j + 2); //guardar el path a t'->N
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(t->s))
	//lo mateix pero a S
		t->s = get_path_textures(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(t->w))
	//lo mateix pero a W
		t->w = get_path_textures(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(t->e))
	//lo mateix per a E
		t->e = get_path_textures(line, j + 2);
	else
		return (2);
	return (0);
}

static int	get_info_map(t_general *g, char **m, int i, int j)
{
	while (m[i][j] == ' ' || m[i][j] == '\t' || m[i][j] == '\n')
		j++; 
	if (ft_isprint(m[i][j]) && !ft_isdigit(m[i][j]))
	{
		if (m[i][j] == 'F' || m[i][j] == 'C')
		{
			if (fill_color_textures(g, &g->txt, m[i], j) == 2)
				return (1);
			return (3);
		}
		else
		{
			if (fill_direction_textures(&g->txt, m[i], j) == 2)
				return (error(g->s_map.path, ERR_TEX_INVALID, 1));
			return (3);
		}
	}
	else if (ft_isdigit(m[i][j]))
	{
		if (create_map(g, m, i) == 1)
			return (error(g->s_map.path, ERR_INVALID_MAP, 1));
		return (0);
	}
	return (4);
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
			ret = get_info_map(g, map, i, j);
			if (ret == 3)
				break ;
			else if (ret == 1)
				return (1); 
			else if (ret == 0)
				return (0); 
			j++; 
		}
		i++;
	}
	return (0);
}
