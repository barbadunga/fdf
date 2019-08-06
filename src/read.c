/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:50:46 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/08/01 14:50:46 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdio.h>

t_vec		*get_data(int fd)
{
	t_vec	*raw_data;
	char	buff[1];

	if (read(fd, NULL, 0) < 0 || !(raw_data = ft_vec_init(2, sizeof(char))))
		return (NULL);
	while (read(fd, buff, 1) > 0)
		ft_vec_add(&raw_data, buff);
	ft_vec_add(&raw_data, "\0");
	ft_putstr(raw_data->data);
	return (raw_data);
}

static int *split(char *line)
{
	int		*arr;
	char	*ptr;
	int		counter;

	ptr = line;
	counter = 0;
	while (*ptr)
		*ptr++ == ' ' ? counter++ : 0;
	if (!(arr = ft_memalloc(sizeof(int) * ((ptr - line) - counter))))
		return (NULL);
	return (arr);
}

t_map		*read_map(char *filename)
{
	t_map	*map;
	char	*line;
	int		i;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(map->point[i] = split(line)))
			// clean all stuff
	}
	map = NULL;
	return (map);
}