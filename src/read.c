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

void	clear_map(t_map **map, t_vec **vec)
{
	if (vec)
		ft_vec_del(vec);
	free(*map);
	exit(-1);
}

int		parse_line(t_vec **vec, t_map **map, char *line)
{
	char	**tab;
	int		i;
	size_t	val;

	i = 0;
	if (!(tab = ft_strsplit(line, ' ')))
		return (-1);
	while (tab[i])
	{
		val = get_hex(tab[i]) << 32u | ft_atoi(tab[i]);
		if (!ft_vec_add(vec, &val))
			return (-1);
		if ((int)val >= (*map)->z_max)
			(*map)->z_max = val;
		if ((int)val <= (*map)->z_min)
			(*map)->z_min = val;
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	if (!(*map)->y_max)
		(*map)->y_max = i;
	return (1);
}

size_t	**new_mesh(t_vec *vec, int rows, int cols)
{
	size_t	**plane;
	int		i;
	int		j;

	i = 0;
	if (!(plane = (size_t **)malloc(sizeof(size_t *) * rows)))
		return (NULL);
	while (i < rows)
	{
		j = 0;
		if (!(plane[i] = (size_t *)malloc(sizeof(size_t) * cols)))
		{
			while (i > 0)
				free(plane + i--);
			free(plane);
			return (NULL);
		}
		while (j < cols)
		{
			plane[i][j] = ((size_t*)vec->data)[i * cols + j];
			j++;
		}
		i++;
	}
	return (plane);
}

t_map	*init_map(void)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	map->y_max = 0;
	map->x_max = 0;
	map->z_max = INT_MIN;
	map->z_min = INT_MAX;
	return (map);
}

t_map	*read_map(char *filename)
{
	t_map	*map;
	t_vec	*vec;
	char	*line;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!(map = init_map()))
		return (NULL);
	if (!(vec = ft_vec_init(8, sizeof(size_t))))
		clear_map(&map, NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (parse_line(&vec, &map, line) < 0)
			clear_map(&map, &vec);
		free(line);
		map->x_max++;
	}
	map->size = (int)vec->total;
	if (!(map->mesh = new_mesh(vec, map->x_max, map->y_max)))
		clear_map(&map, &vec);
	ft_vec_del(&vec);
	return (map);
}
