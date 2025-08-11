/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:34:35 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 14:16:58 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_n_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

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

static void	fill_mem_map(int row, size_t column, int i, t_general *g)
{
	char	*line;

	line = get_next_line(g->s_map.fd);
	while (line != NULL)
	{
		g->s_map.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!g->s_map.file[row])
		{
			error(NULL, ERR_MALLOC, 0);
			return (free_tab((void **)g->s_map.file));
		}
		while (line[i] != '\0')
			g->s_map.file[row][column++] = line[i++];
		g->s_map.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(g->s_map.fd);
	}
	g->s_map.file[row] = NULL;
}

void	check_info(char *path, t_general *g)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	g->s_map.line_count = get_n_lines(path);
	g->s_map.path = path;
	g->s_map.file = ft_calloc(g->s_map.line_count + 1, sizeof(char *));
	if (!(g->s_map.file))
	{
		error(NULL, ERR_MALLOC, 0);
		return ;
	}
	g->s_map.fd = open(path, O_RDONLY);
	if (g->s_map.fd < 0)
		error(path, strerror(errno), 1);
	else
	{
		fill_mem_map(row, column, i, g);
		close(g->s_map.fd);
	}
}
