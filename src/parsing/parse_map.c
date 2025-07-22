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

static int	check_map_elements(t_general *g, char **m_tab)
{
	int	i;
	int	j;

	i = 0;
	g->player.dir = '0';
	while (m_tab[i] != NULL)
	{
		j = 0;
		while (m_tab[i][j])
		{
			while (g->map[i][j] == ' ' || g->map[i][j] == '\t'
			|| g->map[i][j] == '\r'
			|| g->map[i][j] == '\v' || g->map[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", m_tab[i][j])))
				return (error(g->s_map.path, ERR_INV_LETTER, 1));
			if (ft_strchr("NSEW", m_tab[i][j]) && g->player.dir != '0')
				return (error(g->s_map.path, ERR_NUM_PLAYER, 1));
			if (ft_strchr("NSEW", m_tab[i][j]) && g->player.dir == '0')
				g->player.dir = m_tab[i][j];
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_position_is_valid(t_general *g, char **m_tab)
{
	int	i;
	int	j;

	i = (int)g->player.pos_y;
	j = (int)g->player.pos_x;
	if (ft_strlen(m_tab[i - 1]) < (size_t)j
		|| ft_strlen(m_tab[i + 1]) < (size_t)j
		|| check_blank_space(m_tab[i][j - 1]) == 0
		|| check_blank_space(m_tab[i][j + 1]) == 0
		|| check_blank_space(m_tab[i - 1][j]) == 0
		|| check_blank_space(m_tab[i + 1][j]) == 0)
		return (1);
	return (0);
}

static int	check_player_position(t_general *g, char **m_tab)
{
	int	i;
	int	j;

	if (g->player.dir == '0')
		return (error(g->s_map.path, ERR_PLAYER_DIR, -1));
	i = 0;
	while (m_tab[i])
	{
		j = 0;
		while (m_tab[i][j])
		{
			if (ft_strchr("NSEW", m_tab[i][j]))
			{
				g->player.pos_x = (double)j + 0.5;
				g->player.pos_y = (double)i + 0.5;
				m_tab[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(g, m_tab) == -1)
		return (error(g->s_map.path, ERR_PLAYER_POS, -1));
	return (0);
}

static int	check_map_is_at_the_end(t_map *m)
{
	int	i;
	int	j;

	i = m->end_map;
	while (m->file[i])
	{
		j = 0;
		while (m->file[i][j])
		{
			if (m->file[i][j] != ' ' && m->file[i][j] != '\t'
				&& m->file[i][j] != '\r' && m->file[i][j] != '\n'
				&& m->file[i][j] != '\v' && m->file[i][j] != '\f')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_validity(t_general *g, char **m_tab)
{
	if (!g->map)
		return (error(g->s_map.path, ERR_MAP_MISSING, 1));
	if (check_sides(&g->s_map, m_tab) == 1)
		return (error(g->s_map.path, ERR_MAP_NO_WALLS, 1));
	if (g->s_map.height < 3)
		return (error(g->s_map.path, ERR_MAP_TOO_SMALL, 1));
	if (check_map_elements(g, m_tab) == 1)
		return (1);
	if (check_player_position(g, m_tab) == 1)
		return (1);
	if (check_map_is_at_the_end(&g->s_map) == 1)
		return (error(g->s_map.path, ERR_MAP_LAST, 1));
	return (0);
}