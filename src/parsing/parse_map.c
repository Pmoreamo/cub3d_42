/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:33:30 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/04 21:19:32 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	check_map_elements(t_general *g, char **m_tab)
{
	int	i;
	int	j;

	i = 0;
	g->player.dir = '0'; //indiquem que existeix un PLAYER
	while (m_tab[i] != NULL)
	{
		j = 0;
		while (m_tab[i][j])
		{
			while (g->map[i][j] == ' ' || g->map[i][j] == '\t'
			|| g->map[i][j] == '\r'
			|| g->map[i][j] == '\v' || g->map[i][j] == '\f')
				j++; //saltem tots els espais en BLANC
			if (!(ft_strchr("43210NSEW", m_tab[i][j]))) //si no detecta cap CHAR que sigui 10NSEW
				return (error(g->s_map.path, ERR_INV_LETTER, 1)); //retorna error
			if (ft_strchr("NSEW", m_tab[i][j]) && g->player.dir != '0') //si no detecta cap char NSEW
				return (error(g->s_map.path, ERR_NUM_PLAYER, 1)); //retorna error
			if (ft_strchr("NSEW", m_tab[i][j]) && g->player.dir == '0') //si detecta NSEW
				g->player.dir = m_tab[i][j]; //Assigna PLAYER una d'aquestes lletras
			j++; //pasa de columna
		}
		i++; //pasa de fila
	}
	return (0);
}

static int	check_position_is_valid(t_general *g, char **m_tab)
{
	int	i;
	int	j;

	i = (int)g->player.pos_y; //i sera la posicio de PLAYER en el eix Y
	j = (int)g->player.pos_x; //j sera la posicio de PLAYER en el eix X
	if (ft_strlen(m_tab[i - 1]) < (size_t)j //si el la altura es menos que la posicio de PLAYER
		|| ft_strlen(m_tab[i + 1]) < (size_t)j //si la amplitud es menos que la posicio de PLAYER
		|| check_blank_space(m_tab[i][j - 1]) == 0 //si hi ha espai en blanc
		|| check_blank_space(m_tab[i][j + 1]) == 0 //si hi ha espai en blanc
		|| check_blank_space(m_tab[i - 1][j]) == 0 //si hi ha espai en blanc
		|| check_blank_space(m_tab[i + 1][j]) == 0) //si hi ha espai en blanc
		return (1); //retorna error
	return (0);
}

static int	check_player_position(t_general *g, char **m_tab)
{
	int	i;
	int	j;

	if (g->player.dir == '0') //si no hi ha direccio de PLAYER
		return (error(g->s_map.path, ERR_PLAYER_DIR, -1)); //tornar ERROR
	i = 0;
	while (m_tab[i])
	{
		j = 0;
		while (m_tab[i][j])
		{
			if (ft_strchr("NSEW", m_tab[i][j])) //si detecta NSEW
			{
				g->player.pos_x = (double)j + 0.5; //posicio X sera j es suma per centrar el jugador
				g->player.pos_y = (double)i + 0.5; //posicio Y sera i
				m_tab[i][j] = '0'; //aquella posicio es 0, per actualitzar e indicar que es podra pasar per alla
			}
			j++; //passem a la seguent columna
		}
		i++; //passem a la seguent fila
	}
	if (check_position_is_valid(g, m_tab) == -1) //mirem si la posicio que esta PLAYER es valida
		return (error(g->s_map.path, ERR_PLAYER_POS, -1)); //retorn error
	return (0);
}

static int	check_map_is_at_the_end(t_map *m)
{
	int	i;
	int	j;

	i = m->end_map; //asignem a i el index que marca el final del mapa
	while (m->file[i])
	{
		j = 0;
		while (m->file[i][j])
		{
			if (m->file[i][j] != ' ' && m->file[i][j] != '\t'
				&& m->file[i][j] != '\r' && m->file[i][j] != '\n'
				&& m->file[i][j] != '\v' && m->file[i][j] != '\f')
				return (1); //si algun char no es igual a un ESPAI retornar ERROR
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_validity(t_general *g, char **m_tab)
{
	if (!g->map) //si el mapa falla
		return (error(g->s_map.path, ERR_MAP_MISSING, 1)); //retorna ERROR
	if (check_sides(&g->s_map, m_tab) == 1) //si  la funcio falla
		return (error(g->s_map.path, ERR_MAP_NO_WALLS, 1)); //retorn ERROR
	if (g->s_map.height < 3) //si l'ALÇADA del mapa es inferior a 3
		return (error(g->s_map.path, ERR_MAP_TOO_SMALL, 1)); //retorn ERROR
	if (check_map_elements(g, m_tab) == 1) 
		return (1); //retorn ERROR
	if (check_player_position(g, m_tab) == 1)
		return (1); //retorn ERROR
	if (check_map_is_at_the_end(&g->s_map) == 1)
		return (error(g->s_map.path, ERR_MAP_LAST, 1)); //retorn ERROR
	return (0);
}
