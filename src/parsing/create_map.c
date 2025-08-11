/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:51:49 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 14:18:33 by pafranco         ###   ########.fr       */
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
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	g->s_map.end_map = i;
	return (i - index);
}

static int	fill_map(t_map *map, char **n_map, int index)
{
	int	i;
	int	j;

	map->width = biggest_line(map, index);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		n_map[i] = malloc(sizeof(char) * (map->width + 1));
		if (!n_map[i])
			return (error(NULL, ERR_MALLOC, 1));
		while (map->file[index][j] && map->file[index][j] != '\n')
		{
			n_map[i][j] = map->file[index][j];
			j++;
		}
		while (j < map->width)
			n_map[i][j++] = '\0';
		i++;
		index++;
	}
	n_map[i] = NULL;
	return (0);
}

static int	load_map(t_general *g, char **file, int i)
{
	g->s_map.height = n_map_lines(g, file, i);
	g->map = malloc(sizeof(char *) * (g->s_map.height + 1));
	if (!g->map)
		return (error(NULL, ERR_MALLOC, 1));
	if (fill_map(&g->s_map, g->map, i) == 1)
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
			j++;
		while (g->map[i][j])
		{
			if (g->map[i][j] == ' ' && j < (int)ft_strlen(g->map[i]) - 1)
				g->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	create_map(t_general *g, char **file, int i)
{
	if (load_map(g, file, i) == -1)
		return (-1);
	blank_to_wall(g);
	return (0);
}
