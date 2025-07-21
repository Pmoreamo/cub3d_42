/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:18:44 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 17:32:33 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void	free_textures(t_text *txt)
{
	if (txt->N)
		free(txt->N);
	if (txt->S)
		free(txt->S);
	if (txt->W)
		free(txt->W);
	if (txt->E)
		free(txt->E);
	if (txt->floor)
		free(txt->floor);
	if (txt->ceiling)
		free(txt->ceiling);
}

static void	free_map(t_general *gen)
{
	if (gen->s_map.fd > 0)
		close(gen->s_map.fd);
	if (gen->s_map.file)
		free_tab((void **)gen->s_map.file);
	if (gen->map)
		free_tab((void **)gen->map);
}

int	free_data(t_general *gen)
{
	if (gen->text)
		free_tab((void **)gen->text);
	if (gen->txt_pixels)
		free_tab((void **)gen->txt_pixels);
	free_textures(&gen->txt);
	free_map(gen);
	return (-1);
}
