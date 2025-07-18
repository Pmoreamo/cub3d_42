/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:03:10 by marvin            #+#    #+#             */
/*   Updated: 2025/07/14 15:03:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

static int  check_if_rgb_is_valid(int *rgb)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (rgb[i] < 0 || rgb[i] > 255)
            return (error(NULL, ERR_TEX_RGB_VAL, 1));
        i++;
    }
    return (0);
}

static unsigned long   rgb_to_hex(int *rgb)
{
    unsigned long   result;
    int     r;
    int     g;
    int     b;

    r = rgb[0];
    g = rgb[1];
    b = rgb[2];
    result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
    return (result);
}

int check_textures(t_general *gen, t_texture *text)
{
    if (!text->N || !text->S || !text->W || !text->E)
        return (error(gen->s_map.path, ERR_TEX_MISSING, 1));
    if (!text->floor || text->ceiling)
        return (error(gen->s_map.path, ERR_COLOR_MISSING, 1));
    if (check_file(text->N) == 1
        || check_file(text->S) == 1 
        || check_file(text->W) == 1
        || check_file(text->E) == 1
        || check_if_rgb_is_valid(text->floor) == 1
        || check_if_rgb_is_valid(text->ceiling) == 1)
        return (1);
    text->hex_floor = rgb_to_hex(text->floor);
    text->hex_ceiling = rgb_to_hex(text->ceiling);
    return (0);   
}