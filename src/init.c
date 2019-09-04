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

t_point	new_point(int x, int y, int z, t_map *map)
{
	t_point		p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.color = (int)(map->plane[x][y] >> 32);
	if (!p.color && p.z < (map->z_max - map->z_min) / 4)
		p.color = BOTTOM;
	else if (!p.color && p.z > ((map->z_max - map->z_min) * 3) / 4)
		p.color = TOP;
	else if (!p.color)
		p.color = MID;
	return (p);
}

t_point *new_vertex_array(t_map *map)
{
	t_point *vertex = NULL;
	size_t	**data;
	int		x;
	int		y;

	if (!(vertex = (t_point*)malloc(sizeof(t_point) * map->size)))
		return (NULL);
	x = 0;
	data = map->plane;
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
	int	*zbuffer;
	int	i;

	i = 0;
	if (!(zbuffer = (int*)malloc(sizeof(int) * size)))
		return (NULL);
	while (i < size)
		zbuffer[i++] = INT_MIN;
	return (zbuffer);
}
t_fdf	*fdf_init(t_map	**map)
{
	t_fdf	*fdf;

	if (!(fdf = (t_fdf*)malloc(sizeof(t_fdf))))
		return (NULL);
	if (!(fdf->mlx = mlx_init()))
		return (NULL);
	if (!(fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FileDeFler")))
		return (NULL);
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT)))
		return (NULL);
	if (!(fdf->zbuffer = new_zbuffer((*map)->size)))
		return (NULL);
	fdf->vertex = new_vertex_array(*map);
	fdf->map = *map;
	identity(fdf->project, 1.0);
	identity(fdf->rotation, 1.0);
	fdf->scale = 1;
	fdf->del = 1.0;
	fdf->translate[0] = 0;
	fdf->translate[1] = 0;
	fdf->translate[2] = 10;
	fdf->data = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line, &fdf->end);
	return (fdf);
}
