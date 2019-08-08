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

#define RAD(f) f * 3.14 / 180

t_point	rotate(t_point n)
{
	t_point	p;

	p.x = (int)(cos(RAD(45)) * n.x - n.y * sin(RAD(45)));
	p.y = (int)(n.x * sin(RAD(45)) + n.y * cos(RAD(45)));
	p.z = 0;
	p.color = n.color;
	return (p);
}

t_point	new_point(int x, int y, int z, int color)
{
	t_point p;

	p.x = x * 10;
	p.y = y * 10;
	if (z != 0)
		color = 0x0000FF;
	p.z = z * 10;
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
			cur = rotate(new_point(i, j, map->plane[i][j], 0xFF0000));
			if (i + 1 < map->n_rows)
				draw_line(fdf, cur, rotate(new_point(i + 1, j, map->plane[i][j], cur.color)));
			if (j + 1 < map->n_cols)
				draw_line(fdf, cur, rotate(new_point(i, j + 1, map->plane[i][j], cur.color)));
			j++;
		}
		i++;
	}
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 50);
}