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

void 	zoom(t_fdf *fdf, int key)
{
	if (key == 4)
		fdf->view->zoom++;
	if (key == 5)
		fdf->view->zoom--;
}

t_point	new_point(int x, int y, int z, int color)
{
	t_point p;

	p.x = x;
	p.y = y;
	if (z != 0)
		color = 0x0000FF;
	p.z = z;
	p.color = color;
	return (p);
}

void	draw(t_fdf *fdf, t_map *map)
{
	t_point	cur;
	int		i;
	int		j;

	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			cur = new_point(i, j, map->plane[i][j], 0xFF0000);
			if (i + 1 < map->n_rows)
				draw_line(fdf, cur,
						new_point(i + 1, j, map->plane[i][j], cur.color));
			if (j + 1 < map->n_cols)
				draw_line(fdf, cur,
						new_point(i, j + 1, map->plane[i][j], cur.color));
			j++;
		}
		i++;
	}
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
