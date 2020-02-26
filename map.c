/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrova <r11tsa@yahoo.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:41:25 by vpetrova          #+#    #+#             */
/*   Updated: 2020/02/26 18:59:27 by vpetrova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdio.h>
#include <stdlib.h>


int map_init(t_map *map, t_map send)//unsigned int height, unsigned int width,
		//char empty_symbol, char obstacle_symbol, char solution_symbol)
{
	map->positions = malloc(sizeof(char) * send.width * send.height);
	if ((NULL == map->positions) || send.obstacle_symbol == send.empty_symbol ||
		send.empty_symbol == send.solution_symbol || send.solution_symbol == send.obstacle_symbol)
		return (1);
	map->height = send.height;
	map->width = send.width;
	map->empty_symbol = send.empty_symbol;
	map->obstacle_symbol = send.obstacle_symbol;
	map->solution_symbol = send.solution_symbol;
	unsigned int byte;
	byte = 0;
	while (byte < send.height * send.width)
	{
		map->positions[byte] = send.empty_symbol;
		byte++;
	}
	return (0);
}

int		map_is_obstacle(t_map *src, unsigned int row, unsigned int column)
{
	if (row >= src->height)
		return (1);
	if (column >= src->width)
		return (1);

	char value = *(src->positions + (row * src->width) + column);
	return value == src->obstacle_symbol;
}

void map_set_obstacle(t_map *src, unsigned int row, unsigned int column)
{
	if (row >= src->height)
		return;
	if (column >= src->width)
		return;
	*(src->positions + (row * src->width) + column) = src->obstacle_symbol;
}

void map_free(t_map *map)
{
	if (NULL != map->positions)
		free(map->positions);
	map->positions = NULL;
}

