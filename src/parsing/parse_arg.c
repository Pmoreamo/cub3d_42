/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:40:42 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/23 10:58:32 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_dir(char *s)
{
	int		fd; //declarem fd per identificar un fitxer
	char	buf; // 

	fd = open(s, O_DIRECTORY); //obrir el fitxer
	if (fd < 0) //si falla
		return (0); //retornar
	if (read(fd, &buf, 1) < 0) //llegim el fd, guardem el que hi hagui en buf, tot i que no es fara servir, si falla
	{
		close(fd); //tancar el fitxer
		return (1); //tornar 1
	}
	close(fd); //si no falla, tancar el fitxer
	return (0); //tornar 0
}

static int	dot_cub(char *arg)
{
	size_t	len; //declarem len, per guardar la llargada del nom del fitxer.

	len = ft_strlen(arg); //strlen, per saber la llargada del NOM del arxiu
	/* si en el arxiu, en les ultimes quatre lletres no son iguals a .cub, tornar 0*/
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
	/* si len es inferior a 4 || la posicio quatre caracters abans del final, no es igual a .xpm */
	if (len < 4 || !ft_strncmp(arg + len - 4, ".xpm", 4))
		return (1); //retorna 1
	return (0);
}

int	check_file(char *arg, int type)
{
	int	fd; //declarem un fd per identificar un fitxer

	if (is_dir(arg)) //si el arg es un directory
		return (error(arg, ERR_FILE_IS_DIR, 1)); //retorna Error amb missatge personalitzat i 1
	fd = open(arg, O_RDONLY); //obrim el fd amb mode lectura
	if (fd == -1) //si falla
		return (error(arg, strerror(errno), 1)); //retorna ERROR i 1
	close(fd); //un cop comprovat que existeix tanquem el fd
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
