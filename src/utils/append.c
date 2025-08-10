/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tv <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 20:18:38 by tv                #+#    #+#             */
/*   Updated: 2025/08/04 17:42:17 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	**append(void **array, void *next, int *error)
{
	int		i;
	void	**new_array;

	if (*error != 0)
		return (0);
	i = 0;
	while (array != 0 && array[i] != 0)
		i++;
	new_array = ft_calloc(sizeof(void *), i + 2);
	if (new_array == 0)
		*error = 1;
	i = 0;
	while (array != 0 && *error == 0 && array[i] != 0)
	{
		new_array[i] = array[i];
		i++;
	}
	if (array != 0)
		free(array);
	new_array[i] = next;
	return (new_array);
}
