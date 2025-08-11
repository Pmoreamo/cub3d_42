/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:39:57 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 10:43:35 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse(t_general *g, char **av)
{
	if (check_file(av[1], 0) == 1)
		n_exit(g, 1);
	check_info(av[1], g);
	if (get_file_info(g, g->s_map.file) == 1)
		return (free_data(g));
	if (check_map_validity(g, g->map) == 1)
		return (free_data(g));	
	if (check_textures(g, &g->txt) == 1)
		return (free_data(g));
	init_player_dir(g);
	return (0);
}

int	main(int ac, char **av)
{
	t_general g;
	
	if (ac != 2)
		return (error(": ", ERR_USAGE, 1));
	init_s_general(&g); 
	if (parse(&g, av) != 0) 
		exit(EXIT_FAILURE);
	init_mlx(&g); 
	init_textures(&g); 
	render_images(&g); 
	init_input_keys(&g);
	mlx_loop_hook(g.mlx, render, &g); 
	mlx_loop(g.mlx);
}
