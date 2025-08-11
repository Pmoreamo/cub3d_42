/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmorello <pmorello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:40:42 by pmorello          #+#    #+#             */
/*   Updated: 2025/08/11 14:16:03 by pafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_dir(char *s)
{
	int		fd;
	char	buf;

	fd = open(s, O_DIRECTORY);
	if (fd < 0)
		return (0);
	if (read(fd, &buf, 1) < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	dot_cub(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (0);
	return (1);
}

static int	dot_xpm(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len < 4 || !ft_strncmp(arg + len - 4, ".xpm", 4))
		return (1);
	return (0);
}

int	check_file(char *arg, int type)
{
	int	fd;

	if (is_dir(arg))
		return (error(arg, ERR_FILE_IS_DIR, 1));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (error(arg, strerror(errno), 1));
	close(fd);
	if (type == 0)
	{
		if (!dot_cub(arg))
			return (error(arg, ERR_FILE_NOT_CUB, 1));
	}
	if (type == 1)
	{
		if (!dot_xpm(arg))
			return (error(arg, ERR_FILE_NOT_XPM, 1));
	}
	return (0);
}
