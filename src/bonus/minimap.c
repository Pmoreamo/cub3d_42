/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:05:38 by marvin            #+#    #+#             */
/*   Updated: 2025/07/29 14:04:40 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


static int  get_mmp_offset(t_mmap *mmp, int mapsize, int pos)
{
    /*
    Calcula l'offset d'inici del minimapa (en X o Y),
    per centrar el jugador dins del rang de visió (view_dist),
    sempre que sigui possible dins dels límits del mapa.

    Si el jugador està a prop de la vora del mapa, es desplaça l'offset
    perquè no surti fora de límits.
*/

    if (pos > mmp->view_dist && mapsize - pos > mmp->view_dist + 1)
        return (pos - mmp->view_dist);
    if (pos > mmp->view_dist && mapsize - pos <= mmp->view_dist + 1)
        return (mapsize - mmp->size);
    return (0);
}

static int  valid_coord(int coord, int size)
{
    if (coord > size)
        return (1);
    return (0);
}

static char *mmap_line(t_general *g, t_mmap *m, int y)
{
    char    *line;
    int     x;

    /*
    Crea una línia del mapa per al minimapa, a partir d'una fila concreta (`y`).

    La línia s'omple amb caràcters segons el contingut del mapa original:
    - 'P' → si hi ha el jugador
    - '1' → si hi ha una paret
    - '0' → si hi ha terra/camí
    - '\0' → si és fora del mapa o espai no vàlid

    Retorna una cadena nova amb els caràcters representatius per aquella línia.
*/
    line = ft_calloc(m->size + 1, sizeof * line);
    if (!line)
        return (NULL);
    x = 0;
    while (x < m->size && x < g->s_map.width)
    {
        if (valid_coord(y + m->offset_y, g->s_map.height)
            || !valid_coord(x + m->offset_x, g->s_map.width))
            line[x] = '\0';
        else if ((int)g->player.pos_x == (x + m->offset_x)
            && (int)g->player.pos_y == (y + m->offset_y))
            line[x] = 'P';
        else if (g->map[y + m->offset_y][x + m->offset_x] == '1')
            line[x] = '1';
        else if (g->map[y + m->offset_y][x + m->offset_x] == '0')
            line[x] = '0';
        else
            line[x] = '\0';
        x++;
    }
    return (line);
}

static char **create_mmap(t_general*g, t_mmap *mmp)
{
    char    **mmap;
    int     y;

    /*
    Genera tot el contingut del minimapa (mmp->map) com un array de línies,
    cada una creada amb `mmap_line`.

    Retorna un punter a l’array de cadenes (mapa del minimapa) o NULL si falla.
*/
    mmap = ft_calloc(mmp->size + 1, sizeof * mmp);
    if (!mmap)
        return (NULL);
    y = 0;
    while (y < mmp->size && y < g->s_map.height)
    {
        mmap[y] = mmap_line(g, mmp, y);
        if (!mmap[y])
        {
            free_tab((void **)mmap);
            return (NULL);
        }
        y++;
    }
    return (mmap);
}

void    render_mmap(t_general *g)
{
    t_mmap  mmp;

    /*
    Funció principal per renderitzar el minimapa:

    - Inicialitza les dades del minimapa (mida, tile_size, offsets…)
    - Crea una còpia parcial del mapa al voltant del jugador
    - Dibuixa el minimapa i el mostra a la finestra
    - Allibera la memòria temporal usada pel mapa parcial
    */
   
    mmp.map = NULL;
    mmp.img = &g->mmap;
    mmp.view_dist = 4;
    mmp.size = (2 * mmp.view_dist) + 1;
    mmp.tile_size = MMP_SIZE / (2 * mmp.view_dist);
    mmp.offset_x = get_mmp_offset(&mmp, g->s_map.width, (int)g->player.pos_x);
    mmp.offset_y = get_mmp_offset(&mmp, g->s_map.height, (int)g->player.pos_y);
    mmp.map = create_mmap(g, &mmp);
    if (!mmp.map)
    {
        error(NULL, ERR_MALLOC, 0);
        return ;
    }
    minimap_image(g, &mmp);
    free_tab((void **)mmp.map);
}