/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:18 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 10:51:48 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

static int  num_of_map_lines(t_general *gen, char **file, int i)
{
    int index;
    int j;

    index = i;
    while (file[i])
    {
        j = 0;
        check_blank_space_map(file, i, &j);
        if (file[i][j] != '1')
            break;
        i++; 
    }
    gen->s_map.end_map = i;
    return (i - index);
}

static int  fill_map(t_map *map, char **n_map, int index)
{
    int i;
    int j;

    i = 0;
    map->width = check_biggest_line_in_the_map(map, i);
    while (i < map->height)
    {
        j = 0;
        n_map[i] = malloc(sizeof(char) * (map->width + 1));
        if (!n_map)
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

static int  load_map_data(t_general *gen, char **file, int i)
{
    gen->s_map.height = num_of_map_lines(gen, file, i);
    gen->map = malloc(sizeof(char *) * (gen->s_map.height + 1));
    if (!gen->map)
        return (error(NULL, ERR_MALLOC, 1));
    if (fill_map(&gen->s_map, gen->map, i) == 1)
        return (1);
    return (0);
}

static void change_space_into_wall(t_general *gen)
{
    int i;
    int j;

    i = 0;
    while (gen->map[i])
    {
        j = 0;
        check_blank_space_map(gen->map, i, &j);
        while (gen->map[i][++j])
        {
            if (gen->map[i][j] == ' ' && j < (int)ft_strlen(gen->map[i]) - 1)
                gen->map[i][j] = '1';
        }
        i++;
    }
}

int create_map(t_general *gen, char **file, int i)
{
    if (load_map_data(gen, file, i) == -1)
        return (-1);
    change_space_into_wall(gen);
    return (0);
}