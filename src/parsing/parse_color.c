/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:59:10 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/30 20:10:47 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	*rgb(char **tokens)
{
	int		*colors;
	int		i;

	colors = malloc(sizeof(int) * 3); //reservem memoria per a 3 ints
	if (!colors)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit(tokens[i][0])) //sino detecta numeros
		{
			free_tab((void **)tokens); //allibera la taula de tokens
			free(colors); //allibera la memoria de colors
			return (NULL); //tornar NULL
		}
		colors[i] = ft_atoi(tokens[i]); //per cada color, el transforma en un INT, aixi el PC llegira que son COLORS.
		i++; //pasa al seguent color
	}
	free_tab((void **)tokens); //allibrem la taula de tokens
	return (colors); //tornem el CODI DE COLORS
}

static int	*check_format_color(const char *line)
{
	char	**tokens;
	int		count;
	int		i;

	tokens = ft_split(line + 1, ','); //separem els 3 RGB, individualment
	count = 0;
	while (tokens && tokens[count])
		count++; //comptem quants tokens hi ha, sempre sera 3 (R,G,B)
	if (!tokens || count != 3) //sino detecta tokes o el numero no es igual
	{
		i = 0;
		while (tokens && tokens[i])
		{
			free(tokens[i]); //allibarem cada token
			i++; //pasem al seguent token
		}
		free(tokens); //allibarem els tokens en general
		return (NULL);
	}
	return (rgb(tokens));//cridem la funcio RGB
}

int	fill_color_textures(t_general *g, t_text *t, char *line, int j)
{
	while (line[j + 1] == ' ')
		j++;
	if (line[j] && !ft_isdigit(line[j + 1]))
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
