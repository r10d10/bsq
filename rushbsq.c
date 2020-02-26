/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushbsq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:21:46 by vpetrova          #+#    #+#             */
/*   Updated: 2020/02/26 21:56:14 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "rushbs.h"
#include "file.h"
#include "file1.h"
#include <unistd.h>

static void		point_check(t_map *map, unsigned int row, unsigned int column,
				t_solution *solution)
{
	unsigned int		increase;

	increase = solution->best + 1;
	if (!is_square_valid_full(map, row, column, increase))
		return ;
	while (1)
	{
		solution->best = increase;
		solution->row = row;
		solution->column = column;
		increase++;
		if (!is_square_valid_borders(map, row, column, increase))
			return ;
	}
}

static void		solve(t_map *map, t_solution *solution)
{
	unsigned int row;
	unsigned int column;

	row = 0;
	column = 0;
	solution->best = 0;
	while (row < (map->height - solution->best + 1))
	{
		column = 0;
		while (column < (map->width - solution->best + 1))
		{
			point_check(map, row, column, solution);
			column++;
		}
		row++;
	}
}

static void		solve_path(const char *path)
{
	t_solution		solution;
	t_map			map;

	solution.column = 0;
	solution.row = 0;
	if (0 != file_get_map(path, &map))
	{
		write(2, "map error\n", 10);
		return ;
	}
	solve(&map, &solution);
	print_map(&map, solution);
	map_free(&map);
}

int				main(int argc, char **argv)
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
