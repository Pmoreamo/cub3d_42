/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:31:27 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/16 10:52:35 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

int error(char *detail, char *s, int code)
{
    ft_putstr_fd("Cub3D: Error", 2);
    if (detail)
    {
         ft_putstr_fd(": ", 2);
         ft_putstr_fd(detail, 2);
    }
    if (s)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(s, 2);
    }
    ft_putstr_fd("\n", 2);
    return (code);
}

int error_msg(int detail, char *s, int code)
{
    ft_putstr_fd("Cub3D: Error: ", 2);
    ft_putnbr_fd(detail, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(s, 2);
    ft_putstr_fd("\n", 2);
    return (code);
}