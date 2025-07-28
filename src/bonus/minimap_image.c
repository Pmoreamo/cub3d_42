/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:55:10 by marvin            #+#    #+#             */
/*   Updated: 2025/07/28 09:55:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void set_mmp_tile_pixels(t_mmap *mmp, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < mmp->tile_size)
    {
        j = 0;
        while (j < mmp->tile_size)
        {
                set_color_pixel(mmp->img, x + j, i + y, color);
                j++;
                //pinta un tile complet ( i->size, j->size)
        }
        i++;
    }
}


static void draw_mmp_tile(t_mmap *mmp, int x, int y)
{
    /*dibuixa un tile segons el contingut del MAPA (mmp->map[y][x])*/
    if (mmp->map[y][x] == 'P')
        set_mmp_tile_pixels(mmp, x * mmp->tile_size, y * mmp->tile_size, 0x00FF00);
    else if (mmp->map[y][x] == '1')
        set_mmp_tile_pixels(mmp, x * mmp->tile_size, y * mmp->tile_size, 0x808080);
    else if (mmp->map[y][x] == '0')
        set_mmp_tile_pixels(mmp, x * mmp->tile_size, y * mmp->tile_size, 0xE6E6E6);
    else if (mmp->map[y][x] == ' ')
        set_mmp_tile_pixels(mmp, x * mmp->tile_size, y * mmp->tile_size, 0x404040);

}

static void     set_mmp_border(t_mmap *mmp, int color)
{
    int size;
    int x;
    int y;

    /*
    Dibuixa un marc de 5 píxels de gruix al voltant del minimapa.
    El valor `size` representa l'amplada i alçada total de la imatge del minimapa,
    que és la mida del mapa visible en píxels (96) més la mida d'un tile addicional,
    possiblement usat com a marge extra.
    Es pinten els píxels del contorn si estan dins els primers o últims 5 píxels
    de qualsevol costat (esquerra, dreta, dalt o baix).
    */
    size = 96 + mmp->tile_size;
    y = 0;
    while (y < size)
    {
        x = 0;
        while (x <= size)
        {
            if ( x < 5 || x > size - 5 || y < 5 || y > size - 5)
                set_color_pixel(mmp->img, x, y, color);
            x++;
        }
        y++;
    }
}

static void draw_mmp(t_mmap *mmp)
{
    int x;
    int y;

    /* Recoore tot el mapa, per les coordenades Y i X*/
    y = 0;
    while (y < mmp->size)
    {
        x = 0;
        while (x < mmp->size)
        {
            /* en cas de que el mapa falli o arribi al char NULL, para el bucle */
            if (!mmp->map[y] || !mmp->map[y][x]
                || mmp->map[y][x] == '\0')
                break;
            /* dibuixa el TILE */
            draw_mmp_tile(mmp, x, y);
            x++;
        }
        y++;
    }
    /* dibuixa el marc que envolta el minimapa */
    set_mmp_border(mmp, 0x404040);
}

void    minimap_image(t_general *g, t_mmap *mmp)
{
    int i_size;

    /* es per saber el tamany del minimapa
    ocupara 96pixels i suma tile_size per deixar
    marge per MARC */
    i_size = 96 + mmp->tile_size;
    /* inicia la imatge i extreu info*/
    init_img(g, &g->mmap, i_size, i_size);
    /*dibuixa el minimapa*/
    draw_mmp(mmp);
    /*
    Col·loca el minimapa a la finestra, concretament a:
    Y = alçada de win(g->win_height) - (96 píxels + espai extra de 2 tiles d'alçada).
    Exemple:Si tile_size = 2, 96 + (2 * 2) = 100, sumem el tile_size * 2, per deixar un marge visual
    Si win fa 700 píxels d'altura, el mapa es posara al pixel 600 (700 - 100)
    */
    mlx_put_image_to_window(g->mlx, g->win, g->mmap.img, 
        mmp->tile_size, g->win_height 
        - (96 + (mmp->tile_size * 2)));
    /* destrueix la imatge per alliberar memoria */
    mlx_destroy_image(g->mlx, g->mmap.img);
}