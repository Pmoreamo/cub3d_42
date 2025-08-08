/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:39:57 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/08 19:20:56 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse(t_general *g, char **av)
{
	if (check_file(av[1], 0) == 1) //Crida a la funcio de chek_file, si aquest retorna 1
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
	/* 
	int AC = El numero de arguments
	char **AV = El contingut dels arguments
	*/

	t_general	g; //creem una estructura t_general amb el nom g
	
	if (ac != 2) //Si el numero de arguments no es 2
		return (error(": ", ERR_USAGE, 1)); //retorna la funcio error, que printa un missatge i retorna 1
	init_s_general(&g); //Crida a la funcio de init_s_general, que inicia totes les variable de les diferents estructures
	if (parse(&g, av) != 0) //Crida a la funcio de parse, si aquest retorna un valor diferent a 0, surt del programa
		exit(EXIT_FAILURE);
	init_mlx(&g); //inicia la llibreria mlx
	init_textures(&g); //inicia texturas
	render_images(&g); //inicia el render
	init_input_keys(&g); //inicia les tecles
	mlx_loop_hook(g.mlx, render, &g); //fa un loop, que cridara a la funcio (render), amb les dades de &g
	mlx_loop(g.mlx); //inicia un bucle que fa que el programa es quedi obert
	return (0);
}
