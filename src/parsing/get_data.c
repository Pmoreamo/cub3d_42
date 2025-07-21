/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:19:27 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 18:35:33 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*get_path_textures(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	fill_direction_textures(t_text *txt, char *line, int j)
{
	if (line[j] == 'N' && line[j + 1] == 'O' && !(txt->N))
		txt->N = get_path_textures(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(txt->S))
		txt->S = get_path_textures(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(txt->W))
		txt->W = get_path_textures(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(txt->E))
		txt->E = get_path_textures(line, j + 2);
	return (0);
}

static int	get_info_map(t_general *gen, char **m, int i, int j)
{
	while (m[i][j] == ' ' || m[i][j] == '\t' || m[i][j] == '\n')
		j++;
	if (ft_isprint(m[i][j]) && !ft_isdigit(m[i][j]))
	{
		if (m[i][j] == 'F' || m[i][j] == 'C')
		{
			if (fill_color_textures(gen, &gen->txt, m[i], j) == 2)
				return (1);
			return (3);
		}
		else
		{
			if (fill_direction_textures(&gen->txt, m[i], j) == 2)
				return (error(gen->s_map.path, ERR_TEX_INVALID, 1));
			return (3);
		}
	}
	else if (ft_isdigit(m[i][j]))
	{
		if (create_map(gen, m, i) == 1)
			return (error(gen->s_map.path, ERR_INVALID_MAP, 1));
		return (0);
	}
	return (4);
}

int	get_file_info(t_general *gen, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = get_info_map(gen, map, i, j);
			if (ret == 3)
				break ;
			else if (ret == 1)
				return (1);
			else if (ret == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (0);
}
