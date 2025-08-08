/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:40:42 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/08 19:28:11 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_dir(char *s)
{
	int		fd; //declarem fd per identificar el fitxer
	char	buf; //declarem aixo per guardar 

	fd = open(s, O_DIRECTORY); //obrir el fitxer
	if (fd < 0) //si falla
		return (0); //retornar
	if (read(fd, &buf, 1) < 0) //llegim el fd, guardem el que hi hagui en buf, si es menor a 0
	{
		close(fd); //tancar el fitxer
		return (1); //tornar 1
	}
	close(fd); //tancar el fitxer
	return (0); //tornar 0
}

static int	dot_cub(char *arg)
{
	size_t	len; //declarem len, per guardar la llargada del nom del fitxer.

	len = ft_strlen(arg); //strlen, per saber la llargada del NOM del arxiu
	/* si les ultimes quatre lletres no son iguals a .cub, tornar 0*/
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (0);
	return (1);
}

static int	dot_xpm(char *arg)
{
	size_t	len; //per guardar la allarga del NOM del fitxer

	len = ft_strlen(arg); //la llarga del NOM del fitxer
	/* si len es inferior a 4 || les ultimes 4 lletres no es igual a .xpm */
	if (len < 4 || !ft_strncmp(arg + len - 4, ".xpm", 4))
		return (1); //retorna 1
	return (0);
}

int	check_file(char *arg, int type)
{
	int	fd; //serveix per identificar que es un fitxer
	
	if (is_dir(arg)) //Cridem a la funcio que comprova si el argument es un directori
		return (error(arg, ERR_FILE_IS_DIR, 1)); //retorna Error amb missatge personalitzat i 1
	fd = open(arg, O_RDONLY); //obrim el fixter en mode lectura
	if (fd == -1) //si el fitxer falla
		return (error(arg, strerror(errno), 1)); //retorna ERROR i 1
	close(fd); //tanquem el fitxer
	if (type == 0) //si el tipus de arg es 0 (.cub)
	{
		if (!dot_cub(arg)) //si NO es .cub
			return (error(arg, ERR_FILE_NOT_CUB, 1)); //retorna ERROR i 1
	}
	if (type == 1) // si el tipus de arg es 1 (.xpm)
	{
		if (!dot_xpm(arg)) //si NO es .xpm
			return (error(arg, ERR_FILE_NOT_XPM, 1)); //retorna ERROR i 1
	}
	return (0);
}
