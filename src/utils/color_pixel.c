/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranco <pafranco@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:12:16 by pafranco          #+#    #+#             */
/*   Updated: 2025/08/11 14:12:48 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_color_pixel(t_image *i, int x, int y, int color)
{
	int		pixel;

	pixel = y * (i->size_line / 4) + x;
	i->addr[pixel] = color;
}
