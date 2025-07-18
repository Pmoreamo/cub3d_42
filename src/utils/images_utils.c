/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:19:06 by marvin            #+#    #+#             */
/*   Updated: 2025/07/07 12:19:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

void    set_color_pixel(t_image *img, int x, int y, int color)
{
    int pixel;

    pixel = y * (img->size_line / 4) + x;
    img->addr[pixel] = color;
}