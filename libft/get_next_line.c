/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 10:54:24 by pmorello          #+#    #+#             */
/*   Updated: 2025/07/19 14:30:01 by pmorello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_read_fd(int fd, char *buffer)
{
	char	*new_buffer;
	int		b_llegits;

	new_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	b_llegits = 1;
	if (!new_buffer)
		return (free(buffer), buffer = NULL, NULL);
	while (b_llegits > 0 && !gnl_strchr(buffer, '\n'))
	{
		b_llegits = read(fd, new_buffer, BUFFER_SIZE);
		if (b_llegits > 0)
		{
			new_buffer[b_llegits] = '\0';
			buffer = gnl_strjoin(buffer, new_buffer);
		}
	}
	free(new_buffer);
	if (b_llegits < 0)
		return (free(buffer), buffer = NULL, NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = gnl_read_fd(fd, buffer);
	if (!buffer)
		return (free(buffer), buffer = NULL, NULL);
	line = gnl_read_line(buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = gnl_new_line(buffer);
	return (line);
}
