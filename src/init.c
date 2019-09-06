/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:08:21 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/08/01 13:08:21 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_all(t_fdf **fdf, t_map **map)
{
	if (fdf)
	{
		free(*fdf);
		free((*fdf)->vertex);
	}
	free((*map)->mesh);
	free(*map);
}

t_point	new_point(int x, int y, int z, t_map *map)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	if (map && !(p.color = (int)(map->mesh[x][y] >> 32)))
		p.color = 0xFFFFFF;
	return (p);
}

t_point	*new_vertex_array(t_map *map)
{
	t_point *vertex;
	size_t	**data;
	int		x;
	int		y;

	if (!(vertex = (t_point*)malloc(sizeof(t_point) * map->size)))
		return (NULL);
	x = 0;
	data = map->mesh;
	while (x < map->x_max)
	{
		y = 0;
		while (y < map->y_max)
		{
			vertex[x * map->y_max + y] = new_point(x, y, data[x][y], map);
			y++;
		}
		x++;
	}
	return (vertex);
}

int		*new_zbuffer(int size)
{
	int		*zbuffer;
	int		i;

	i = 0;
	if (!(zbuffer = (int*)malloc(sizeof(int) * size)))
		return (NULL);
	while (i < size)
		zbuffer[i++] = INT_MIN;
	return (zbuffer);
}

t_fdf	*fdf_init(t_map **map)
{
	t_fdf	*fdf;

	if (!(fdf = (t_fdf*)malloc(sizeof(t_fdf))))
		clear_all(NULL, map);
	if (!(fdf->mlx = mlx_init()))
		clear_all(&fdf, map);
	if (!(fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FileDeFler")))
		clear_all(&fdf, map);
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT)))
		clear_all(&fdf, map);
	if (!(fdf->zbuffer = new_zbuffer((*map)->size)))
		return (NULL);
	if (!(fdf->vertex = new_vertex_array(*map)))
		clear_all(&fdf, map);
	fdf->map = *map;
	diagonalize(fdf->project, 1.0);
	diagonalize(fdf->rotation, 1.0);
	fdf->scale = 1;
	fdf->del = 1.0;
	fdf->translate[0] = 0;
	fdf->translate[1] = 0;
	fdf->translate[2] = 10;
	fdf->data = mlx_get_data_addr(fdf->img, &fdf->bpp,
			&fdf->size_line, &fdf->end);
	return (fdf);
}
