/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:43:19 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/09 20:30:45 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_img(t_general *g, t_image *i, int width, int height)
{
	/* 
	*g : es un punter que accedeix a la estructura de GENERAL i els seus elemets
	*i : es un punter que accedeix a la estructura de IMAGE i els seus elemets
	width : amplada
	heigt : alcada 
	*/
	
	init_s_image(i);
	/* iniciem els valors de la estructura de la imatge */
	i->image = mlx_new_image(g->mlx, width, height);
	/* Dins la estructura de IMAGE, entrem en la variable image. 
	En aquesta variable li dic que guardi el resultat de la funcio MLX, 
	que en aquest cas es la creacio de una imatge en negre  */
	if (i->image == NULL)
		clean_exit(g, error("mlx", ERR_MLX_IMG, 1));
	/* si falla, com es un punter i accedeix a la memoria, sha de alliberar */
	i->addr = (int *)mlx_get_data_addr(i->image, &i->pixel_bits,
			&i->size_line, &i->endian);
	/* Dins de la estructura de IMAGE, entrem a la variable de addr.
	En aquest variable crido a la funcio MLX, aquesta funcio agafa
	entra en la estrctura de IMAGE i guarda cada variable al seu
	lloc corresponent:
	IMAGE, guarda un punter a la imatge 
	PIXEL_BITS, guardem quants bits ocupa cada pixel, 
	SIZE_LINE, quants bytes ocupa 1 linea de la imatge, 
	ENDIA, el ordre dels bytes 
	ADDR, retorna un punter a les dades de la imatge, per poder modificar els pixels*/
	return ;
}

void	init_textures_img(t_general *g, t_image *i, char *p)
{
	/*
	*g : punter per accedir a la estructura GENERAL i els seus elements
	*i : punter per accedir a la estructura IMAGE i els seus elements
	*p : per guardar el path a on estan els arxius .xpm
	*/

	init_s_image(i);
	/* iniciem els valors de la struct de la imatge */
	i->image = mlx_xpm_file_to_image(g->mlx, p, &g->txt.size, &g->txt.size);
	/* Dins la estuctura IMAGE, entrem a la variable image.
	En aquesta variable li dic que guardi el resultat de la funcio MLX,
	que en aquest cas es una copia del arxiu .xpm, preparda per fer servir */
	if (i->image == NULL)
		clean_exit(g, error("mlx", ERR_MLX_IMG, 1));
	/* si falla, alliberar la memoria */
	i->addr = (int *)mlx_get_data_addr(i->image, &i->pixel_bits,
			&i->size_line, &i->endian);
	/* Dins de la estructura de IMAGE, entrem a la variable de addr.
	En aquest variable crido a la funcio MLX, aquesta funcio agafa
	entra en la estrctura de IMAGE i guarda cada variable al seu
	lloc corresponent:
	IMAGE, guarda un punter a la imatge
	PIXEL_BITS, guardem quants bits ocupa cada pixel, 
	SIZE_LINE, quants bytes ocupa 1 linea de la imatge, 
	ENDIA, el ordre dels bytes 
	ADDR, retorna un punter a les dades de la imatge, per poder modificar els pixels*/
	return ;
}

void	init_mlx(t_general *g)
{
	/*
	*g : punter a la estructura GENERAL i els seus elements
	*/
	g->mlx = mlx_init();
	/* A dins de MLX, guardo un punter que "conecta" el programa amb 
	la llibreria mlx */
	if (!g->mlx)
		clean_exit(g, error("mlx", ERR_MLX_START, 1));
	g->win = mlx_new_window(g->mlx, g->win_width, g->win_height, "cub3d");
	/* a dins de win, es creara una finestra i guardo el seu punter */
	if (!g->win)
		clean_exit(g, error("mlx", ERR_MLX_WIN, 1));
}
