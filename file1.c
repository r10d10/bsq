/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrova <r11tsa@yahoo.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:41:37 by vpetrova          #+#    #+#             */
/*   Updated: 2020/02/26 20:32:59 by vpetrova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "file1.h"
#include "ftatoi.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		read_obstacles(t_map *map, unsigned int row, char *ptr)
{
	unsigned int	column;

	column = 0;
	while (*(ptr + column) != '\0')
	{
		if (column >= map->width)
			return (1);
		if (*(ptr + column) == map->obstacle_symbol)
		{
			map_set_obstacle(map, row, column);
		}
		else if (*(ptr + column) != map->empty_symbol)
		{
			return (1);
		}
		column++;
	}
	return (column != map->width);
}

int		read_additional_line(t_map *map, unsigned int row)
{
	char			*ptr;

	if (0 != read_file_line_known_length(&ptr, map->width + 1) ||
		(NULL == ptr))
		return (1);
	return (read_obstacles(map, row, ptr));
}

int		read_header_and_first_line(t_map *map)
{
	char			*ptr;
	t_map			send;

	if (0 != read_file_line(&ptr) || (NULL == ptr))
		return (1);
	send.width = 0;
	while (*(ptr + send.width) != '\0')
		send.width++;
	send.obstacle_symbol = ptr[send.width - 2];
	send.solution_symbol = ptr[send.width - 1];
	send.empty_symbol = ptr[send.width - 3];
	ptr[send.width - 3] = '\0';
	send.height = ft_atoi(ptr);
	if (0 != read_file_line(&ptr) || (NULL == ptr))
		return (1);
	send.width = 0;
	while (*(ptr + send.width) != '\0')
		send.width++;
	if (0 != map_init(map, send))
		return (1);
	if (0 != read_obstacles(map, 0, ptr) || send.width == 0 || send.height < 1)
	{
		map_free(map);
		return (1);
	}
	return (0);
}

void		close_file(void)
{
	if (g_status.fd != 0)
		close(g_status.fd);
	if (NULL != g_status.buffer)
		free(g_status.buffer);
	g_status.buffer = NULL;
}

int		file_get_map(const char *path, t_map *map)
{
	unsigned int	row;
	char			*ptr;

	if (0 != open_file(path))
		return (1);
	if (0 != (read_header_and_first_line(map)))
	{
		close_file();
		return (1);
	}
	row = 1;
	while (row < map->height)
	{
		if (0 != read_additional_line(map, row))
		{
			map_free(map);
			close_file();
			return (1);
		}
		row++;
	}
	if (0 != read_file_line(&ptr) || ptr != NULL)
	{
		map_free(map);
		close_file();
		return (1);
	}
	close_file();
	return (0);
}
