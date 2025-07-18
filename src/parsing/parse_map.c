/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:10:31 by marvin            #+#    #+#             */
/*   Updated: 2025/07/18 14:01:59 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

/* comprueba los elementos del mapa*/
static int  check_map_elements(t_general *gen, char **map)
{
    int     i;
    int     j;
    
    i = 0;
    //decimos que player existe
    gen->player.exist = '0';
    //Recorremos i del mapa
    while (map[i] != NULL)
    {
        j = 0;
        //recorremos i y j del mapa
        while (map[i][j])
        {
            //recorre los chars de una linea para ver si hay espacios en blanco y los salta
            while (check_blanks(map[i][j]))
                j++;
            //si no encuentra los caracteres "1,0,N,S,W o E, printa error"
            if (!ft_strchr("10NSWE", map[i][j]))
                return (error(gen->s_map.path, ERR_INV_LETTER, 1));
            //si encuentra los caracteres "1, 0, N, S, W,o E y la existalizacion de player, es mas de 1, printa error"
            if (ft_strchr("NSWE", map[i][j]) && gen->player.exist != '0')
                return (error(gen->s_map.path, ERR_NUM_PLAYER, 1));
            //si encuentra los chars "1,0,N,S,W o E" y la existalizacion de player, es solo 1,  assinga existalizacio a la posicion de i y j
            if (ft_strchr("NSWE", map[i][j]) && gen->player.exist == '0')
                gen->player.exist = map[i][j];
            j++;
        }
        i++;
    }
    return (0);
}

/*mira la posicion de player no este en blanco*/
static int  check_map_position(t_general *gen, char **map)
{
    int i;
    int j;
    int k;

    //definimos todas las direcciones, ARRIBA, ABAJO, DER, IZQ.
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    i = gen->player.pos_x;
    j = gen->player.pos_y;
    k = 0;
    //mientras K sea menor a las possible dirreciones
    while (k < 4)
    {
        //ni y nj, seran las coordenadas vecina.
        int ni = i + dx[k];
        int nj = j + dy[k];
        // si algo es menor de 0, falla o es mas grande que la mida del mapa
        if (ni < 0 || nj < 0 || map[i] == NULL || nj >= (int)ft_strlen(map[ni]))
            return (-1);
        //si la coord de ni y nj es espacio blanco, devuelve -1
        if (check_blank_space(map[ni][nj] == -1))
            return (-1);
    }
    return (0);
}

/* la pos del player*/
static int  check_map_player_pos(t_general *gen, char **map)
{
    int     i;
    int     j;

    //si existe player
    if (gen->player.exist == '0')
        return (error(gen->s_map.path, ERR_PLAYER_DIR, 1));
    i = 0;
    //recorremos i del mapa
    while (map[i])
    {
        j = 0;
        //recorremos las lineas del mapa
        while (map[i][j])
        {
            //si encuentra algun char "NSWE"
            if (ft_strchr("NSWE", map[i][j]))
            {
                //asigna la pos de player
                gen->player.pos_x = i;
                gen->player.pos_y = j;
                //asigna los char NSWE, como 0
                map[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    //comprueba si la posicion de player esta bien dentro del mapa
    if (check_map_position(gen, map) == -1)
        return (error(gen->s_map.path, ERR_PLAYER_POS, 1));
    return (0);
}

/* comprueba si el mapa esta cerrado*/
static int  check_map_end(t_map *s_map, char **map)
{
    int     i;
    int     j;
    
    i = s_map->end_map;
    while (s_map->file[i])
    {
        j = 0;
        while (s_map->file[i][j])
        {
            if (check_blank_space(map[i][j]))
                return (-1);
            j++;
        }
        i++;
    }
    return (0);
}

/* comprueba que el mapa este cerrado con 1*/
static int  check_top_and_bottom_map(char **map, int i, int j)
{
    if (!map || !map[i] || !map[i][j])
        return (-1);
    while (check_blanks(map[i][j]))
        i++;
    while (map[i] && map[i][j])
    {
        if (map[i][j] != '1')
            return (1);
        i++;
    }
    return (0);
}

static int     check_map_sides(t_map *map, char **tmp_map)
{
    int     i;
    int     j;

    if (check_top_and_bottom_map(tmp_map, 0, 0) == 1)
        return (1);
    i = 1;
    while ( i < (map->height - 1))
    {
        j = ft_strlen(tmp_map[i]) - 1;
        if (tmp_map[i][j] != '1')
            return (1);
        i++;
    }
    if (check_top_and_bottom_map(tmp_map, i, 0) == 1)
        return (1);
    return (0);
}

int     check_map(t_general *gen, char **map)
{
    if (!gen->map)
        return (error(gen->s_map.path, ERR_MAP_MISSING, 1));
    else if (check_map_sides(&gen->s_map, map) == 1)
        return (error(gen->s_map.path, ERR_MAP_NO_WALLS, 1));
    else if (gen->s_map.height < 3)
        return (error(gen->s_map.path, ERR_MAP_TOO_SMALL, 1));
    else if (check_map_elements(gen, map) == 1)
        return (1);
    else if (check_map_player_pos(gen, map) == 1)
        return (1);
    else if (check_map_end(&gen->s_map, map) == -1)
        return (error(gen->s_map.path, ERR_MAP_LAST, 1));
    return (0);
}