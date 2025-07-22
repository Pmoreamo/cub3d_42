/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:35:33 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/21 18:09:44 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_blank_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (1);
	else
		return (0);
}

size_t	biggest_line(t_map *m, int i)
{
	size_t	b_len;

	b_len = ft_strlen(m->file[i]);
	while (m->file[i])
	{
		if (ft_strlen(m->file[i]) > b_len)
			b_len = ft_strlen(m->file[i]);
		i++;
	}
	return (b_len);
}
