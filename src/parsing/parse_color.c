/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:59:10 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 10:53:36 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	*rgb_array(char **tokens)
{
	int	*colors;
	int	i;
	
	colors = malloc(sizeof(int) * 3);
	if (!colors)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit(tokens[i][0]))		{
			free_tab((void **)tokens);
			free(colors);
			return (NULL);
		}
		colors[i] = ft_atoi(tokens[i]);
		i++;
	}
	free_tab((void **)tokens);
	return (colors);
}

static int	*check_format_color(const char *line)
{
	char	**tokens;
	int		count;
	int		i;

	tokens = ft_split(line + 1, ',');
	count = 0;
	while (tokens[count])
		count++;
	if (!tokens || count != 3)
	{
		i = 0;
		while (tokens && tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
		return (NULL);
	}
	return (rgb_array(tokens));
}

int	fill_color_textures(t_general *g, t_text *t, char *line, int j)
{
	int	i;

	i = j + 1;
	while (line[i] == ' ')
		i++;
	if (!ft_isdigit(line[i]))
		return (error(g->s_map.path, ERR_FLOOR_CEILING, 2));
	if (!t->ceiling && line[j] == 'C')
	{
		t->ceiling = check_format_color(line + j + 1);
		if (!t->ceiling)
			return (error(g->s_map.path, ERR_COLOR_CEILING, 2));
	}
	else if (!t->floor && line[j] == 'F')
	{
		t->floor = check_format_color(line + j + 1);
		if (!t->floor)
			return (error(g->s_map.path, ERR_COLOR_FLOOR, 2));
	}
	else
		return (error(g->s_map.path, ERR_FLOOR_CEILING, 2));
	return (0);
}
