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

	vertex->x = (int)((x - y) * cos(DEG2RAD(30)));
	vertex->y = (int)( -vertex->z + (x + y) * sin(DEG2RAD(30)));
}

void	transform(t_fdf *fdf, t_point *vertex)
{
	int	i;

	i = 0;
	while (i < fdf->map->size)
	{
		vertex[i].x *= fdf->view->scale;
		vertex[i].y *= fdf->view->scale;
		vertex[i].z *= fdf->view->scale;
		vertex[i].x += fdf->view->x_offset;
		vertex[i].y += fdf->view->y_offset;
		if (fdf->project)
			isometric(&vertex[i]);
		i++;
	}
	fdf->view->scale = 1;
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

void 	zoom(t_fdf *fdf, int key)
{
	if (key == 4)
		fdf->view->scale++;
	if (key == 5)
		fdf->view->scale = fdf->view->scale > 1? fdf->view->scale - 1 : 1;
}

void	move(t_fdf *fdf, int key)
{
	if (key == 123)
		fdf->view->y_offset = -5;
	if (key == 124)
		fdf->view->y_offset = 5;
	if (key == 125)
		fdf->view->x_offset = 5;
	if (key == 126)
		fdf->view->x_offset = -5;
}

void	draw(t_fdf *fdf, t_map *map)
{
	t_point *vertex;
	int		i;

	i = 0;
	vertex = fdf->vertex;
	fill(fdf, 0, 0, HEIGHT, WIDTH, 0);
	transform(fdf, vertex);
	while (i < map->size)
	{
		if (i % map->n_cols < map->n_cols - 1)
			draw_line(fdf, vertex[i], vertex[i + 1]);
		if (i < map->size - map->n_cols)
			draw_line(fdf, vertex[i], vertex[i + map->n_cols]);
		i++;
	}
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
