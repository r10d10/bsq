/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrova <r11tsa@yahoo.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:41:37 by vpetrova          #+#    #+#             */
/*   Updated: 2020/02/26 20:32:59 by vpetrova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

const unsigned int g_buffer_initial = 64;

int		increase_buffer(void)
{
	char			*aux;
	unsigned int	i;

	aux = malloc(2 * g_status.buffer_size);
	if (NULL == aux)
		return (1);
	i = 0;
	while (i < g_status.buffer_size)
	{
		aux[i] = g_status.buffer[i];
		i++;
	}
	free(g_status.buffer);
	g_status.buffer = aux;
	g_status.buffer_size *= 2;
	return (0);
}

int		open_file(const char *path)
{
	int fd;

	if (NULL != path)
	{
		fd = open(path, O_RDONLY);
		if (fd < 0)
			return (1);
	}
	else
	{
		fd = 0;
	}
	g_status.fd = fd;
	g_status.buffer_size = g_buffer_initial;
	g_status.buffer = malloc(g_status.buffer_size);
	if (NULL == g_status.buffer)
	{
		if (0 != fd)
			close(fd);
		return (1);
	}
	return (0);
}

int		read_file_line_known_length(char **ptr, unsigned int length)
{
	ssize_t r;

	while (length > g_status.buffer_size - 1)
	{
		if (0 != increase_buffer())
			return (1);
	}
	r = read(g_status.fd, g_status.buffer, length);
	if (r != length)
	{
		return (1);
	}
	if (g_status.buffer[length - 1] != '\n')
	{
		return (1);
	}
	g_status.buffer[length - 1] = '\0';
	*ptr = g_status.buffer;
	return (0);
}

int		read_file_line(char **ptr)
{
	unsigned int	cnt;
	ssize_t			r;

	cnt = 0;
	r = read(g_status.fd, g_status.buffer, 1);
	if (r < 0)
		return (1);
	else if (r == 0)
	{
		*ptr = NULL;
		return (0);
	}
	while (g_status.buffer[cnt++] != '\n')
	{
		r = read(g_status.fd, &g_status.buffer[cnt], 1);
		if (r <= 0)
			return (1);
		if (cnt >= g_status.buffer_size - 1)
			if (0 != increase_buffer())
				return (1);
	}
	g_status.buffer[cnt - 1] = '\0';
	*ptr = g_status.buffer;
	return (0);
}
