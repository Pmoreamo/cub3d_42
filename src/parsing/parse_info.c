/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:34:35 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 18:08:59 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_n_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY); //obrir el fitxer
	if (fd < 0) //si falla 
		error(path, strerror(errno), errno); //retorn ERROR
	else
	{
		line = get_next_line(fd); //linea, ser la funcio get_next_line
		while (line != NULL) //mentres no sigui la ultima linea
		{
			line_count++; //suma +1 al contador de lineas
			free(line); //allibera la linea, per guardar la seguent
			line = get_next_line(fd); //tornas a assignar GNL a la linea
		}
		close(fd); //tancar el fd
	}
	return (line_count); //tornar el numero de LINEAS
}

static void	fill_mem_map(int row, size_t column, int i, t_general *g)
{
	char	*line;

	line = get_next_line(g->s_map.fd); //agafa una linea del mapa
	while (line != NULL)
	{
		g->s_map.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char)); 
		//per cada linea del mapa[], reservar tants bytes de memoria com chars hi hagui a la linea + 1 (NULL)
		if (!g->s_map.file[row]) //si falla
		{
			error(NULL, ERR_MALLOC, 0); //error
			return (free_tab((void **)g->s_map.file)); //alliberar la memoria del file
		}
		while (line[i] != '\0') //mentres la linea no sigui null
			g->s_map.file[row][column++] = line[i++]; //guardar en cada fila la LINEA del mapa
		g->s_map.file[row++][column] = '\0'; //posar NULL al final de cada fila
		column = 0; //reinicar les variables per la seguent linea
		i = 0;
		free(line); //alliberar la memoria per la seguent linea
		line = get_next_line(g->s_map.fd); //pasar a la seguent linea
	}
	g->s_map.file[row] = NULL; //marcar que la ultima fila del mapa es NULL
}

void	check_info(char *path, t_general *g)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	g->s_map.line_count = get_n_lines(path); //guardem el numero de LINEAS que te el mapa
	g->s_map.path = path; //guardar el PATH, dins la estructura de s_map
	g->s_map.file = ft_calloc(g->s_map.line_count + 1, sizeof(char *)); 
	//reservem memoria per guardar cada linea del mapa com una cadena
	if (!(g->s_map.file)) //si la RESERVA MEMORIA falla
	{
		error(NULL, ERR_MALLOC, 0); //retorna ERROR
		return ;
	}
	g->s_map.fd = open(path, O_RDONLY); //obrim el mapa, nomes lectura
	if (g->s_map.fd < 0) //si falla
		error(path, strerror(errno), 1); //ERROR
	else
	{
		fill_mem_map(row, column, i, g); //guardem com a cadenes de text el mapa dins la MEMORIA del ordinador
		close(g->s_map.fd); //tanquem mapa
	}
}
