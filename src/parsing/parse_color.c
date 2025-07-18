/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:21:46 by marvin            #+#    #+#             */
/*   Updated: 2025/07/18 13:54:03 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/general.h"

/*
static int	has_non_digit(char *line)
{
	int		i;
	int		value;
	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (1);
		i++;
	}
	value = ft_atoi(&line[i]);
	return (value);	
}*/

static int	*convert_rgb(char **tokens)
{
	int		*rgb;
	int		i;

	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit(tokens[i][0]))
		{
			free_tab((void **)tokens);
			free(rgb);
			return (NULL);
		}
		rgb[i] = ft_atoi(tokens[i]);
		i++;
	}
	free_tab((void **)tokens);
	return (rgb);
}

// Analitza una línia i retorna un array RGB, o NULL si falla
static int	*parse_rgb(const char *line)
{
	char	**tokens = ft_split(line + 1, ',');
	int		count = 0;

	while (tokens && tokens[count])
		count++;
	if (!tokens || count != 3)
	{
		free_tab((void **)tokens);
		return (NULL);
	}
	return (convert_rgb(tokens));
}

// Omple textures amb colors de sostre i terra, segons la línia del mapa
int	fill_color_textures(t_general *gen, t_texture *text, char *line, int j)
{
	if (line[j + 1] && line[j + 1] != ' ' && !ft_isdigit(line[j + 1]))
		return (error(gen->s_map.path, ERR_FLOOR_CEILING, 2));
	if (!text->ceiling && line[j] == 'C')
	{
		text->ceiling = parse_rgb(line + j + 1);
		if (!text->ceiling)
			return (error(gen->s_map.path, ERR_COLOR_CEILING, 2));
	}
	else if (!text->floor && line[j] == 'F')
	{
		text->floor = parse_rgb(line + j + 1);
		if (!text->floor)
			return (error(gen->s_map.path, ERR_COLOR_FLOOR, 2));
	}
	else
		return (error(gen->s_map.path, ERR_FLOOR_CEILING, 2));
	return (0);
}