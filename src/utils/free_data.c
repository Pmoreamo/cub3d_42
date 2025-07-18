/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:25:33 by marvin            #+#    #+#             */
/*   Updated: 2025/07/09 16:42:43 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

void    free_tab(void **tab)
{
    size_t i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    if (tab)
    {
        free(tab);
        tab = NULL;
    }
}

static void free_textures(t_texture *text)
{
    if (text->N)
        free(text->N);
    if (text->S)
        free(text->S);
    if (text->W)
        free(text->W);
    if (text->E)
        free(text->E);
    if (text->floor)
        free(text->floor);
    if (text->ceiling)
        free(text->ceiling);
}

static void free_map(t_general *gen)
{
    if (gen->s_map.fd > 0)
        close(gen->s_map.fd);
    if (gen->s_map.file)
        free_tab((void **)gen->s_map.file);
    if (gen->map)
        free_tab((void **)gen->map);
}

int     free_data(t_general *gen)
{
    if (gen->textures)
        free_tab((void **)gen->textures);
    if (gen->text_pixels)
        free_tab((void **)gen->text_pixels);
    free_textures(&gen->text);
    free_map(gen);
    return (-1);
}