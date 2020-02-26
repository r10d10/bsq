/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrova <r11tsa@yahoo.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:55:32 by vpetrova          #+#    #+#             */
/*   Updated: 2020/02/26 00:16:02 by vpetrova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

typedef struct		s_status {
	int				fd;
	char			*buffer;
	unsigned int	buffer_size;
}					t_status;

static				t_status g_status;

int					increase_buffer(void);

int					open_file(const char *path);

int					read_file_line_known_length(char **ptr,
								unsigned int length);

int					read_file_line(char **ptr);

#endif
