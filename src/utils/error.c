/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:42:10 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 17:33:11 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	error(char *msg, char *err, int c)
{
	ft_putstr_fd("Cub3D: ", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
	}
	if (err)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err, 2);
	}
	ft_putstr_fd("\n", 2);
	return (c);
}
