/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrova <r11tsa@yahoo.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 23:49:34 by vpetrova          #+#    #+#             */
/*   Updated: 2020/02/26 00:06:05 by vpetrova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE1_H
# define FILE1_H

# include "map.h"

int		read_obstacles(t_map *map, unsigned int row, char *ptr);

int		read_additional_line(t_map *map, unsigned int row);

int		read_header_and_first_line(t_map *map);

void	close_file(void);

int		file_get_map(const char *path, t_map *map);

#endif
