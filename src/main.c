/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:39:57 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 18:39:51 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse(t_general *gen, char **av)
{
	if (check_file(av[1], 0) == 1)
		n_exit(gen, 1);
	check_info(av[1], gen);
	if (get_file_info(gen, gen->s_map.file) == 1)
		return (free_data(gen));
	if (check_map_validity(gen, gen->map) == 1)
		return (free_data(gen));
	if (check_textures(gen, &gen->txt) == 1)
		return (free_data(gen));
	init_player_dir(gen);
	return (0);
}

int	main(int ac, char **av)
{
	t_general	gen;

	if (ac != 2)
		return (error(": ", ERR_USAGE, 1));
	init_s_general(&gen);
	if (parse(&gen, av) != 0)
		exit(EXIT_FAILURE);
	init_mlx(&gen);
	init_textures(&gen);
	draw_raycast(&gen);
	init_input_keys(&gen);
	mlx_loop_hook(gen.mlx, render, &gen);
	mlx_loop(gen.mlx);
	return (0);
}
