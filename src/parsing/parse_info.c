/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:34:35 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/19 15:39:22 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_n_lines(char *path)
{
	int	fd;
	char	*line;
	int	line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error(path, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

static void	fill_mem_map(int row, size_t column, int i, t_general *gen)
{
	char	*line;

	line = get_next_line(gen->s_map.fd);
	while (line != NULL)
	{
		gen->s_map.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!gen->s_map.file[row])
		{
			error(NULL, ERR_MALLOC, 0);
			return (free_tab((void **)gen->s_map.file));
		}
		while (line[i] != '\0')
			gen->s_map.file[row][column++] = line[i++];
		gen->s_map.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(gen->s_map.fd);
	}
	gen->s_map.file[row] = NULL;
}


void	check_info(char *path, t_general *gen)
{
	int	row;
	int	i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	gen->s_map.line_count = get_n_lines(path);
	gen->s_map.path = path;
	gen->s_map.file = ft_calloc(gen->s_map.line_count + 1, sizeof(char *));
	if (!(gen->s_map.file))
	{
		error(NULL, ERR_MALLOC, 0);
		return;
	}
	gen->s_map.fd = open(path, O_RDONLY);
	if (gen->s_map.fd < 0)
		error(path, strerror(errno), 1);
	else
	{
		fill_mem_map(row, column, i, gen);
		close(gen->s_map.fd);
	}
}
