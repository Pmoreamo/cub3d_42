/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:55:10 by marvin            #+#    #+#             */
/*   Updated: 2025/08/08 11:44:10 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void set_mmp_tile_pixels(t_mmap *mmp, t_image *img, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < mmp->tile_size)
    {
        j = 0;
        while (j < mmp->tile_size)
        {
                set_color_pixel(img, x + j, y + i, color);
                j++;
                //pinta un tile complet ( i->size, j->size)
        }
        i++;
    }
}


static void draw_mmp_tile(t_mmap *mmp,t_image *i, int x, int y)
{
    /*dibuixa un tile segons el contingut del MAPA (mmp->map[y][x])*/
    if (mmp->map[y][x] == 'P')
        set_mmp_tile_pixels(mmp, i, x * mmp->tile_size, y * mmp->tile_size, 0x00FF00);
    else if (mmp->map[y][x] == '1')
        set_mmp_tile_pixels(mmp, i, x * mmp->tile_size, y * mmp->tile_size, 0x808080);
    else if (mmp->map[y][x] == '0')
        set_mmp_tile_pixels(mmp, i, x * mmp->tile_size, y * mmp->tile_size, 0xE6E6E6);
    else if (mmp->map[y][x] == ' ')
        set_mmp_tile_pixels(mmp, i, x * mmp->tile_size, y * mmp->tile_size, 0x404040);
    else
        set_mmp_tile_pixels(mmp, i, x * mmp->tile_size, y * mmp->tile_size, 0x0000FF);
}

static void     set_mmp_border(t_mmap *mmp, int color, t_image *i)
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
    size = MMP_SIZE + mmp->tile_size;
    y = 0;
    while (y <= size + 5)
    {
        x = 0;
        while (x <= size + 5)
        {
            if ( x >= size || y >= size)
                set_color_pixel(i, x, y, color);
            else
                set_color_pixel(i, x, y, 0x808080);
            x++;
        }
        y++;
    }
}

static void draw_mmp(t_mmap *mmp, t_image *i)
{
    int x;
    int y;

    /* Recoore tot el mapa, per les coordenades Y i X*/
    y = 0;
    set_mmp_border(mmp, 0x404040, i);
    while (y < mmp->size)
    {
        x = 0;
        while (x < mmp->size)
        {
            /* en cas de que el mapa falli o arribi al char NULL, para el bucle */
         	if (!mmp->map[y] || mmp->map[y][x] == '\0')
				break ;
            /* dibuixa el TILE */
            draw_mmp_tile(mmp, i, x, y);
            x++;
        }
        y++;
    }
	/* dibuixa el marc que envolta el minimapa */ 
}

void    minimap_image(t_general *g, t_mmap *mmp, t_image *i)
{
    if (g == 0)
        exit(0);
    draw_mmp(mmp, i);
}
