/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:59:10 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/19 19:23:01 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	*rgb(char **tokens)
{
	int		*colors;
	int		i;

	colors = malloc(sizeof(int) * 3);
	if (!colors)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit(tokens[i][0]))
		{
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
	while (tokens && tokens[count])
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
	return (rgb(tokens));
}


int		fill_color_textures(t_general *gen, t_text *txt, char *line, int j)
{
	if (line[j + 1] && line[j + 1] != ' ' && !ft_isdigit(line[j + 1]))
		return (error(gen->s_map.path, ERR_FLOOR_CEILING, 2));
	if (!txt->ceiling && line[j] == 'C')
	{
		txt->ceiling = check_format_color(line + j + 1);
		if (!txt->ceiling)
			return (error(gen->s_map.path, ERR_COLOR_CEILING, 2));
	}
	else if (!txt->floor && line[j] == 'F')
	{
		txt->floor = check_format_color(line + j + 1);
		if (!txt->floor)
			return (error(gen->s_map.path, ERR_COLOR_FLOOR, 2));
	}
	else
		return (error(gen->s_map.path, ERR_FLOOR_CEILING, 2));
	return (0);
}
