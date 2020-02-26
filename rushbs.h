/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushbs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollero- <aollero@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:58:32 by aollero-          #+#    #+#             */
/*   Updated: 2020/02/26 21:33:47 by aollero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSHBS_H
# define RUSHBS_H

# include "main.h"
# include "file1.h"

void			print_map(t_map *map, t_solution solution);

int				is_square_valid_borders(t_map *map, unsigned int row,
				unsigned int column, unsigned int increase);

int				is_square_valid_full(t_map *map, unsigned int row,
				unsigned int column, unsigned int increase);

#endif
