/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:51:49 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/19 19:39:39 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	n_map_lines(t_general *gen, char **file, int i)
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
			break;
		i++;
	}
	gen->s_map.end_map = i;
	return (i - index);
}

static int	fill_map(t_map *map, char **n_map, int index)
{
	int	i;
	int	j;

	map->width = biggest_line(map, index);
	i = 0;
	while ( i < map->height)
	{
		j = 0;
		n_map[i] = malloc(sizeof(char) * (map->width + 1));
		if (!n_map)
			return (error(NULL, ERR_MALLOC, -1));
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

static int	load_map(t_general *gen, char **file, int i)
{
	gen->s_map.height = n_map_lines(gen, file, i);
	gen->map = malloc(sizeof(char *) * (gen->s_map.height + 1));
	if (!gen->map)
		return (error(NULL, ERR_MALLOC, 1));
	if (fill_map(&gen->s_map, gen->map, i) == 1)
		return (1);
	return (0);
}

static void	blank_to_wall(t_general *gen)
{
	int	i;
	int	j;

	i = 0;
	while (gen->map[i])
	{
		j = 0;
		while (gen->map[i][j] == ' ' || gen->map[i][j] == '\t'
			|| gen->map[i][j] == '\r'
			|| gen->map[i][j] == '\v' || gen->map[i][j] == '\f')
				j++;
		while (gen->map[i][++j])
		{
			if (gen->map[i][j] == ' ' && j < (int)ft_strlen(gen->map[i] - 1))
				gen->map[i][j] = '1';
		}
		i++;
	}
}

int		create_map(t_general *gen, char **file, int i)
{
	if (load_map(gen, file, i) == -1)
		return (-1);
	blank_to_wall(gen);
	return (0);
}
