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
#include "mlx.h"

t_point	new_point(int x, int y, int z, int color)
{
	t_point p;

	p.x = x;
	p.y = y;
	if (z != 0)
		color = 0x0000FF;
	p.z = z * 10;
	p.color = color;
	return (p);
}

t_point *new_vertex_array(t_map *map)
{
	t_point *vertex = NULL;
	int		**data;
	int		x;
	int		y;

	if (!(vertex = (t_point*)malloc(sizeof(t_point) * map->size)))
		return (NULL);
	x = 0;
	data = map->plane;
	while (x < map->n_rows)
	{
		y = 0;
		while (y < map->n_cols)
		{
			vertex[x * map->n_cols + y] = new_point(x, y, data[x][y], 0xFF0000);
			y++;
		}
		x++;
	}
	return (vertex);
}

t_fdf	*fdf_init(t_map	**map)
{
	t_fdf	*fdf;
	t_view	*view;

	if (!(fdf = (t_fdf*)malloc(sizeof(t_fdf))))
		return (NULL);
	if (!(fdf->mlx = mlx_init()))
		return (NULL);
	if (!(fdf->win = mlx_new_window(fdf->mlx, HEIGHT, WIDTH, "FileDeFler")))
		return (NULL);
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT)))
		return (NULL);
	if (!(view = (t_view*)malloc(sizeof(t_view))))
		return (NULL);
	fdf->vertex = new_vertex_array(*map);
	fdf->map = *map;
	fdf->view = view;
	fdf->view->scale = 1;
	fdf->view->x_offset = 0;
	fdf->view->y_offset = 0;
	fdf->project = 0;
	fdf->data = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line, &fdf->end);
	return (fdf);
}