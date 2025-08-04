/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tv <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:18:38 by tv                #+#    #+#             */
/*   Updated: 2025/08/02 20:27:45 by tv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	**append(void **array, void *next)
{
	int		i;
	void	**new_array;

	i = 0;
	if (array = 0)
	{
		new_array = ft_calloc(sizeof(void *), 2);
		new_array[0] = next;
		return (new_array);
	}
	while (array[i] != 0)
		i++;
	new_array = ft_calloc(sizeof(void *), i + 1);
	i = 0;
	while (array[i] != 0)
		new_array[i] = array[i++];
	array[i] = next;
}
