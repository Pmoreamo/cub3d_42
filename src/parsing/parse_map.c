/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:33:30 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/19 15:35:34 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_map_elements(t_general *gen, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	gen->player.dir = '0';
	while (map_tab[i] != NULL)
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (gen->map[i][j] == ' ' || gen->map[i][j] == '\t'
			|| gen->map[i][j] == '\r'
			|| gen->map[i][j] == '\v' || gen->map[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", map_tab[i][j])))
				return (error(gen->s_map.path, ERR_INV_LETTER, 1));
			if (ft_strchr("NSEW", map_tab[i][j]) && gen->player.dir != '0')
				return (error(gen->s_map.path, ERR_NUM_PLAYER, 1));
			if (ft_strchr("NSEW", map_tab[i][j]) && gen->player.dir == '0')
				gen->player.dir = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_position_is_valid(t_general *gen, char **map_tab)
{
	int	i;
	int	j;

	i = (int)gen->player.pos_y;
	j = (int)gen->player.pos_x;
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j
		|| check_blank_space(map_tab[i][j - 1]) == 0
		|| check_blank_space(map_tab[i][j + 1]) == 0
		|| check_blank_space(map_tab[i - 1][j]) == 0
		|| check_blank_space(map_tab[i + 1][j]) == 0)
		return (1);
	return (0);
}

static int	check_player_position(t_general *gen, char **map_tab)
{
	int	i;
	int	j;

	if (gen->player.dir == '0')
		return (error(gen->s_map.path, ERR_PLAYER_DIR, -1));
	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (ft_strchr("NSEW", map_tab[i][j]))
			{
				gen->player.pos_x = (double)j + 0.5;
				gen->player.pos_y = (double)i + 0.5;
				map_tab[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(gen, map_tab) == -1)
		return (error(gen->s_map.path, ERR_PLAYER_POS, -1));
	return (0);
}

static int	check_map_is_at_the_end(t_map *map)
{
	int	i;
	int	j;

	i = map->end_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_validity(t_general *gen, char **map_tab)
{
	if (!gen->map)
		return (error(gen->s_map.path, ERR_MAP_MISSING, 1));
	if (check_sides(&gen->s_map, map_tab) == 1)
		return (error(gen->s_map.path, ERR_MAP_NO_WALLS, 1));
	if (gen->s_map.height < 3)
		return (error(gen->s_map.path, ERR_MAP_TOO_SMALL, 1));
	if (check_map_elements(gen, map_tab) == 1)
		return (1);
	if (check_player_position(gen, map_tab) == 1)
		return (1);
	if (check_map_is_at_the_end(&gen->s_map) == 1)
		return (error(gen->s_map.path, ERR_MAP_LAST, 1));
	return (0);
}
