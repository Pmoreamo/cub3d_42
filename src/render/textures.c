/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:04:32 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 11:13:47 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

void    init_texture_pixels(t_general *gen)
{
    int i;

    if (gen->text_pixels)
        free_tab((void **)gen->text_pixels);
    gen->text_pixels = ft_calloc(gen->win_height + 1, sizeof * gen->text_pixels);
    if (!gen->text_pixels)
        clean_exit(gen, error(NULL, ERR_TEX_INVALID, 1));
    i = 0;
    while (i < gen->win_height)
    {
        gen->text_pixels[i] = ft_calloc(gen->win_width + 1, sizeof * gen->text_pixels);
        if (!gen->text_pixels[i])
            clean_exit(gen, error(NULL, ERR_MALLOC, 1));
        i++;
    }
}

static void get_textures_index(t_general *gen, t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->dir_x < 0)
            gen->text.index = 2;
        else    
            gen->text.index = 3;
    }
    else
    {
        if (ray->dir_y > 0)
            gen->text.index = 1;
        else
            gen->text.index = 0;
    }
}

void	update_texture_pixels(t_general *data, t_texture *text, t_ray *ray, int x)
{
	int	y;
	int	color;

	get_textures_index(data, ray);
	// Càlcul de la coordenada X de la textura
	text->x = (int)(ray->wall_x * text->size);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0))
		text->x = text->size - text->x - 1;
	// Càlcul de l'avanç de píxel i posició inicial a la textura
	text->step = (double)text->size / ray->line_height;
	text->pos = (ray->draw_start - data->win_height / 2.0 + ray->line_height / 2.0) * text->step;
    y = ray->draw_start;
    color = 0;
	// Pinta columna de píxels
    while (y < ray->draw_end)
	{
		text->y = ((int)text->pos) & (text->size - 1);
		text->pos += text->step;
		color = data->textures[text->index][text->size * text->y + text->x];
		// Aplicar ombrejat segons direcció
		if (text->index == 0 || text->index == 3)
		    color = (color >> 1) & 0x7F7F7F;  // Equivalent més clar que 8355711
		// Només pintar si el color no és transparent (opcional)
		if (color > 0)
			data->text_pixels[y][x] = color;
        y++;
	}
}