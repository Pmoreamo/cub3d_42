/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:59:10 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/30 21:02:22 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	*rgb_array(char **tokens, int *rgb)
{
	int	i;
	
	i = 0;
	while (tokens[i])
	{
		rgb[i] = ft_atoi(tokens[i]);
		if (rgb[i] == -1 || !ft_isdigit(rgb[i]))
		{
			free_tab((void **)tokens);
			free(rgb);
			return (NULL);
		}
		i++;
	}
	free_tab((void **)tokens); //allibrem la taula de tokens
	return (rgb); //tornem el CODI DE COLORS
}

static int	*check_format_color(const char *line)
{
	char	**tokens;
	int		count;
	int		*rgb;

	tokens = ft_split(line, ','); //separem els 3 RGB, individualment
	count = 0;
	while (tokens[count])
		count++; //comptem quants tokens hi ha, sempre sera 3 (R,G,B)
	if (!tokens || count != 3) //sino detecta tokes o el numero no es igual
	{
		free_tab((void **)tokens);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3); //reservem memoria per a 3 elements amb un pes de int bytes
	if (!rgb)
	{
		error(NULL, ERR_MALLOC, 0);
		return (0);
	}
	return (rgb_array(tokens, rgb));//cridem la funcio RGB array
}

int	fill_color_textures(t_general *g, t_text *t, char *line, int j)
{
	int	i;

	i = j + 1;
	while (line[i] == ' ')
		i++;
	if (!ft_isdigit(line[i]))
	/* si la linea [j + 1] no espai i no es numero, ERROR*/
		return (error(g->s_map.path, ERR_FLOOR_CEILING, 2));
	if (!t->ceiling && line[j] == 'C') //Si no hi ha textura de CEILING i detecta C
	{
		t->ceiling = check_format_color(line + j + 1); //Ceiling sera igual a la funcio de CHECK_FORMAT_COLOR
		if (!t->ceiling)
			return (error(g->s_map.path, ERR_COLOR_CEILING, 2)); //si falla, ERROR
	}
	else if (!t->floor && line[j] == 'F')
	{
		/*el mateix pero ammb el terra*/
		t->floor = check_format_color(line + j + 1);
		if (!t->floor)
			return (error(g->s_map.path, ERR_COLOR_FLOOR, 2));
	}
	else
		return (error(g->s_map.path, ERR_FLOOR_CEILING, 2));
		/*si no detecta ni F ni C, ERROR*/
	return (0);
}
