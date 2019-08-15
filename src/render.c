/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:38:47 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/08/07 21:38:47 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>

void	isometric(t_point *vertex)
{
	int		x;
	int		y;

	x = vertex->x;
	y = vertex->y;

	vertex->x = (int)((x + y) * cos(DEG2RAD(30)));
	vertex->y = (int)( -vertex->z + (x - y) * sin(DEG2RAD(30)));
}

void	fill(t_fdf *fdf, int x, int y, int height, int width, int color)
{
	int *dat;
	int	start;

	start = y;
	dat = (int *)fdf->data;
	height += x;
	width += y;
	while (x < height && x < HEIGHT)
	{
		y = start;
		while (y < width && y < WIDTH)
			dat[x * WIDTH + y++] = color;
		x++;
	}
}

t_point project(t_fdf *fdf, t_point vertex)
{
	vertex.x = (int)(vertex.x * fdf->view->scale);
	vertex.y = (int)(vertex.y * fdf->view->scale);
	vertex.z = (int)(vertex.z * fdf->view->scale);
	rotate_x(fdf, &vertex);
	rotate_y(fdf, &vertex);
	rotate_z(fdf, &vertex);
	vertex.x += fdf->view->x_offset;
	vertex.y += fdf->view->y_offset;
	if (fdf->project)
		isometric(&vertex);
	return (vertex);
}

void	set_to_default(t_fdf *fdf)
{
	fdf->project = 0;
}

void	draw(t_fdf *fdf, t_map *map)
{
	t_point *vertex;
	int		i;

	i = 0;
	vertex = fdf->vertex;
	fill(fdf, 0, 0, HEIGHT, WIDTH, 0);
	while (i < map->size)
	{
		if (i % map->n_cols < map->n_cols - 1)
			draw_line(fdf, project(fdf, vertex[i]), project(fdf, vertex[i + 1]));
		if (i < map->size - map->n_cols)
			draw_line(fdf, project(fdf, vertex[i]), project(fdf, vertex[i + map->n_cols]));
		i++;
	}
	set_to_default(fdf);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
