/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushbsq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrova <r11tsa@yahoo.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:21:46 by vpetrova          #+#    #+#             */
/*   Updated: 2020/02/26 20:32:58 by vpetrova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "file.h"
#include "file1.h"
#include <unistd.h>

/*
** In the case that more than one solution exists, we’ll choose to represent
** thesquare that’s closest to the top of the map, then the one that’s most to
** theleft
*/

void			print_map(t_map *map, t_solution solution)
{
	unsigned int		i;
	unsigned int		row_count;

	i = 0;
	row_count = 0;
	while (i < map->height * map->width)
	{
		if ((((solution.row  + row_count) * map->width + solution.column <= i) &&
			((solution.row  + row_count) * map->width + solution.column + solution.best > i))
			&& (row_count < solution.best))
		{
			write(1, &map->solution_symbol, 1);
		}
		else
			write(1, &map->positions[i], 1);
		if ((i!= 0 && (i + 1) % (map->width) ==  0))
		{
			write(1, "\n", 1);
			if ((i + 1) / (map->width) >= solution.row + 1)
				row_count++;
		}
		i++;
	}
			if ((map->height * map->width <=  1))
			write(1, "\n", 3);
}

static int		is_square_valid_borders(t_map *map, unsigned int row,
				   unsigned int column, unsigned int increase)
{
	unsigned int 		row_scan;
	unsigned int		column_scan;

	if (((row + increase) > map->height) ||
	    ((column + increase) > map->width))
		return 0;
	row_scan = row;
	while (row_scan < row + increase) {
		if (map_is_obstacle(map, row_scan, column + increase - 1))
			return 0;
		row_scan++;
	}
	column_scan = column;
	while (column_scan < column + increase) {
		if (map_is_obstacle(map, row + increase - 1, column_scan))
			return 0;
		column_scan++;
	}
	return 1;
}

static int		is_square_valid_full(t_map *map, unsigned int row,
				unsigned int column, unsigned int increase)
{
	unsigned int		row_scan;
	unsigned int		column_scan;

	if (((row + increase) > map->height) ||
	    ((column + increase) > map->width))
		return (0);

	row_scan = row;
	while (row_scan < row + increase) {
		column_scan = column;
		while (column_scan < column + increase) {
			if (map_is_obstacle(map, row_scan, column_scan))
				return 0;

			column_scan++;
		}
		row_scan++;
	}
	return (1);
}

static void		point_check(t_map *map, unsigned int row, unsigned int column,
		 t_solution *solution)
{
	unsigned int		increase;

	increase = solution->best + 1;

	if (!is_square_valid_full(map, row, column, increase))
		return;
	while (1)
	{
		solution->best = increase;
		solution->row = row;
		solution->column = column;
		increase++;

		if (!is_square_valid_borders(map, row, column, increase))
			return;
	}
}

static void solve(t_map *map, t_solution *solution)
{
	unsigned int row;
	unsigned int column;

	row = 0;
	column = 0;
	solution->best = 0;
	while(row < (map->height - solution->best + 1))
	{
		column = 0;
		while(column < (map->width - solution->best + 1))
		{
			point_check(map, row, column, solution);
			column++;
		}
		row++;
	}
}


static void solve_path(const char *path)
{
	t_solution		solution;
	t_map			map;

	solution.row = solution.column = 0;
	if (0 != file_get_map(path, &map)) {
		write(2, "map error\n",10);
		return;
	}
	solve(&map, &solution);
	print_map(&map, solution);
	map_free(&map);
}

int main		(int argc, char **argv)
{
	int map_counter;

	map_counter = 1;
	if (argc == 1)
		solve_path(NULL);
	else
		while (map_counter < argc)
			solve_path(argv[map_counter++]);
	return (0);
}
