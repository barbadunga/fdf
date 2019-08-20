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

void	print(double matrix[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%f\t", matrix[i][j]);
		printf("\n");
	}
}

void	calculate_transform(double project[4][4], t_view *view)
{
	double		rot[4][4];
	double		scale[4][4];
	double		translate[4][4];

	identity(rot);
	identity(scale);
	identity(translate);
	xrotate(rot, DEG2RAD(view->alpha));
	yrotate(rot, DEG2RAD(view->beta));
	zrotate(rot, DEG2RAD(view->gamma));
	print(rot);
	scale[0][0] = view->scale;
	scale[1][1] = view->scale;
	scale[2][2] = view->scale;
	translate[0][3] = view->x_offset;
	translate[1][3] = view->y_offset;
	concat_matrix(scale, project, project);
	concat_matrix(rot, project, project);
	concat_matrix(translate, project, project);
}

void	draw(t_fdf *fdf, t_map *map)
{
	t_point *vertex;
	int		i;

	i = 0;
	vertex = fdf->vertex;
	fill(fdf, 0, 0, HEIGHT, WIDTH, 0);
	calculate_transform(fdf->project, fdf->view);
	while (i < map->size)
	{
		if (i % map->n_cols < map->n_cols - 1)
			draw_line(fdf, project(fdf->project, vertex[i]), project(fdf->project, vertex[i + 1]));
		if (i < map->size - map->n_cols)
			draw_line(fdf, project(fdf->project, vertex[i]), project(fdf->project, vertex[i + map->n_cols]));
		i++;
	}
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
