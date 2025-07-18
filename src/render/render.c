/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 08:34:05 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 11:13:12 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

void    paint_pixel_in_frame(t_general *gen, t_image *img, int x, int y)
{
    if (gen->text_pixels[y][x] > 0)
        set_color_pixel(img, x, y, gen->text_pixels[y][x]);
    else if (y < gen->win_height / 2)
        set_color_pixel(img, x, y, gen->text.hex_ceiling);
    else if (y < gen->win_height - 1)
        set_color_pixel(img, x,y,gen->text.hex_floor);
}

static void put_frame_in_window(t_general *gen)
{
    t_image img;
    int x;
    int y;

    img.image = NULL;
    init_img(gen, &img, gen->win_width, gen->win_height);
    y = 0;
    while (y < gen->win_height)
    {
        x = 0;
        while (x < gen->win_width)
        {
            paint_pixel_in_frame(gen, &img, x, y);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(gen->mlx, gen->win, img.image, 0, 0);
    mlx_destroy_image(gen->mlx, img.image);
}

static void draw_raycast(t_general *gen)
{
    init_texture_pixels(gen);
    init_s_ray(&gen->ray);
    raycasting(gen, &gen->player);
    put_frame_in_window(gen);
}

/*
void    draw_images(t_general *gen)
{
    draw_raycast(gen);
}
*/

int     render(t_general *gen)
{
    gen->player.has_moved += move_player(gen);
    if (gen->player.has_moved == 0)
        return (0);
    draw_raycast(gen);
    return (0);
}