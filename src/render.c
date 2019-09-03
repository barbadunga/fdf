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

void	calculate_transform(t_fdf *fdf, double	rot[4][4], double project[4][4])
{
	project[0][0] *= fdf->scale;
	project[1][1] *= fdf->scale;
	project[2][2] *= fdf->scale;
	project[3][2] = 1 / -140.0;
	concat_matrix(rot, project, project);
}

void	draw(t_fdf *fdf, t_map *map)
{
	t_point *vertex;
	t_point	*projected;
	int		i;

	i = 0;
	vertex = fdf->vertex;
	fill(fdf, 0, 0, HEIGHT, WIDTH, 0);
	calculate_transform(fdf, fdf->rotation, fdf->project);
	if (!(projected = (t_point*)malloc(sizeof(t_point) * map->size)))
		return ;
	while (i < map->size)
	{
		projected[i] = project(fdf, fdf->project, vertex[i]);
		i++;
	}
	i = 0;
	while (i < map->size)
	{
		if (i % map->y_max < map->y_max - 1)
			draw_line(fdf, projected[i], projected[i + 1]);
		if (i < map->size - map->y_max)
			draw_line(fdf, projected[i], projected[i + map->y_max]);
		i++;
	}
	identity(fdf->project, 1.0);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
