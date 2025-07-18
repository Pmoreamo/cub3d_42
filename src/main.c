/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:04:08 by marvin            #+#    #+#             */
/*   Updated: 2025/07/18 13:20:33 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/general.h"

static void    init_mlx(t_general *gen)
{
    gen->mlx = mlx_init();
    if (!gen->mlx)
        clean_exit(gen, error("mlx", ERR_MLX_START, 1));
    gen->win = mlx_new_window(gen->mlx, gen->win_height, gen->win_width, "Cub3D");
    if (!gen->win)
        clean_exit(gen, error("mlx", ERR_MLX_WIN, 1));
}

static int  parse(t_general *gen, char **av)
{
    if (check_file(av[1]) == 1)
        n_exit(gen, 1);
    check_data(av[1], gen);
    if (get_file_data(gen, gen->s_map.file) == 1)
        return (free_data(gen));
    if (check_map(gen, gen->map) == 1)
        return (free_data(gen));
    if (check_textures(gen, &gen->text) == 1)
        return (free_data(gen));
    init_player_dir(gen);
    return (0);
}

int main(int argc, char **av)
{
    t_general gen;

    if (argc < 1 || argc > 2)
        return (error("Usage", ERR_USAGE, 1));
    init_s_general(&gen);
    if (parse(&gen, av) != 0)
        exit (EXIT_FAILURE);
    init_mlx(&gen);
    init_textures(&gen);
    render(&gen);
    init_input_hooks(&gen);
    mlx_loop_hook(gen.mlx, render, &gen);
    mlx_loop(&gen);
    return (0);
}