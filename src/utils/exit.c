/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:56:08 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 12:48:42 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

void    n_exit(t_general *gen, int code)
{
    if (!gen)
        exit(code);
    exit(code);
}

void    clean_exit(t_general *gen, int code)
{
    if (!gen)
        exit(code);
    if (gen->win && gen->mlx)
        mlx_destroy_window(gen->mlx, gen->win);
    if (gen->mlx)
    {
        mlx_destroy_display(gen->mlx);
        mlx_loop_end(gen->mlx);
        free(gen->mlx);
    }
    free(gen);
    exit(code);
}

int quit(t_general *gen)
{
    clean_exit(gen, 0);
    return (0);
}