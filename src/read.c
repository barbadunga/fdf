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

/*
 * Need to catch all fails of allocation!
 */

static int	parse_line(t_vec **vec, t_map **map, char *line)
{
	char	**tab;
	int		i;
	int		val;

	i = 0;
	if (!(tab = ft_strsplit(line, ' ')))
		return (-1);
	while (tab[i])
	{
		val = ft_atoi(tab[i++]);
		ft_vec_add(vec, &val);
	}
	if (!(*map)->n_cols)
		(*map)->n_cols = i;
	return (1);
}

static int		**create_plane(t_vec *vec, int rows, int cols)
{
	int	**plane;
	int	i;
	int j;

	i = 0;
	if (!(plane = (int**)malloc(sizeof(int*) * rows)))
		return (NULL);
	while (i < rows)
	{
		j = 0;
		if (!(plane[i] = (int*)malloc(sizeof(int) * cols)))
			return (NULL);
		while (j < cols)
		{
			plane[i][j] = ((int *)vec->data)[i * cols + j + 1];
			j++;
		}
		i++;
	}
	return (plane);
}

static t_map	*init_map(void)
{
	t_map *map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	map->n_cols = 0;
	map->n_rows = 0;
	return (map);
}

t_map		*read_map(char *filename)
{
	t_map	*map;
	t_vec	*vec;
	char	*line;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	if (!(map = init_map()))
		return (NULL);
	if (!(vec = ft_vec_init(8, sizeof(int))))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(&vec, &map, line);
		map->n_rows++;
	}
	map->size = (int)vec->total;
	map->plane = create_plane(vec, map->n_rows, map->n_cols);
	ft_vec_del(&vec);
	return (map);
}
