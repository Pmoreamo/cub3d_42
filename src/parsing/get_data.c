/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:36:20 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 14:34:35 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

static char *get_text_path(char *line, int j)
{
    int len;
    int i;
    char *path;
    
    while (line[j] && (line[j] == ' ' || line[j]== '\t'))
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

static int  fill_directions_text(t_texture *text, char *line, int j)
{
    if (line[j + 2]&& !(line[j + 2] == ' ' || line[j + 2] == '\t'))
        return(2);
    if (line[j] == 'N' && line[j + 1] == 'O' && !(text->N))
        text->N = get_text_path(line, j + 2);
    else if (line[j] == 'S' && line[j + 1] == 'O' && !(text->S))
        text->S = get_text_path(line, j + 2);
    else if (line[j] == 'W' && line[j + 1] == 'E' && !(text->W))
        text->W = get_text_path(line, j + 2);
    else if (line[j] == 'E' && line[j + 1] == 'A' && !(text->E))
        text->E = get_text_path(line, j + 2);
    else
        return (2);
    return(0);
}

static int  ignore_whitespaces_get_info(t_general *gen, char **map, int i, int j)
{
    while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
        j++;
    if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
    {
        if (check_if_is_color(map[i], j) == 0)
        {
            if (fill_directions_text(&gen->text, map[i], j) == 2)
                return (error(gen->s_map.path, ERR_TEX_INVALID, 1));
            return (3);
        }
        else
        {
            if (fill_color_textures(gen, &gen->text, map[i], j) == 2)
                return (1);
            return(3);
        }
    }
    else if (ft_isdigit(map[i][j]))
    {
        if (create_map(gen, map, i) == 1)
            return (error(gen->s_map.path, ERR_INVALID_MAP, 1));
        return (0);
    }
    return (4); 
}

int     get_file_data(t_general *gen, char **map)
{
    int i;
    int j;
    int ret;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            ret = ignore_whitespaces_get_info(gen, map, i, j);
            if (ret == 3)
                break;
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