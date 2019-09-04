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

/*
 * Need to catch all fails of allocation!
 */

static int	parse_line(t_vec **vec, t_map **map, char *line)
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
		ft_vec_add(vec, &val);
		if ((int)val >= (*map)->z_max)
			(*map)->z_max = val;
		if ((int)val <= (*map)->z_min)
			(*map)->z_min = val;
		i++;
	}
	if (!(*map)->y_max)
		(*map)->y_max = i;
	return (1);
}

static size_t		**create_plane(t_vec *vec, int rows, int cols)
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
			return (NULL);
		while (j < cols)
		{
			plane[i][j] = ((size_t*)vec->data)[i * cols + j];
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
	map->y_max = 0;
	map->x_max = 0;
	map->z_max = INT_MIN;
	map->z_min = INT_MAX;
	return (map);
}

t_map		*read_map(char *filename)
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
	{
		free(map);
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(&vec, &map, line);;
		map->x_max++;
	}
	map->size = (int)vec->total;
	map->plane = create_plane(vec, map->x_max, map->y_max);
	ft_vec_del(&vec);
	return (map);
}
