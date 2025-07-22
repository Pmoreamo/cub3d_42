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

static int	parse(t_general *g, char **av)
{
	if (check_file(av[1], 0) == 1) //si check_file falla
		n_exit(g, 1); //surt del programa
	check_info(av[1], g); //revisa la informacio
	if (get_file_info(g, g->s_map.file) == 1) //si la info del arxiu falla
		return (free_data(g)); //allibera tot i surt
	if (check_map_validity(g, g->map) == 1) //si la info del mapa falla
		return (free_data(g)); //allibera tot i surt
	if (check_textures(g, &g->txt) == 1) //si la info de les texturas falla
		return (free_data(g)); //allibera tot i surt
	init_player_dir(g); //inicia la posicio del jugador
	return (0);
}

int	main(int ac, char **av)
{
	t_general	g;

	
	if (ac != 2) //si els arguments no son 2
		return (error(": ", ERR_USAGE, 1)); //retorna la funcio ERROR
	init_s_general(&g); //inicia la funcio s_general
	if (parse(&g, av) != 0) //si el parse no es 0 (FUNCIONA)
		exit(EXIT_FAILURE); //surt del programa
	init_mlx(&g); //inicia MLX
	init_textures(&g); //inicia texturas
	draw_raycast(&g); //inicia el render
	init_input_keys(&g); //inicia les tecles
	mlx_loop_hook(g.mlx, render, &g); //fa un loop, que cridara a la funcio (render), amb les dades de &g
	mlx_loop(g.mlx); //inicia un bucle que fa que el programa es quedi obert
	return (0);
}
