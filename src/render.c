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

void	fill(t_fdf *fdf, t_point p, int height, int width)
{
	int			*dat;
	const int	color = 0;
	int			start;

	start = p.y;
	dat = (int *)fdf->data;
	height += p.x;
	width += p.y;
	while (p.x < height && p.x < HEIGHT)
	{
		p.y = start;
		while (p.y < width && p.y < WIDTH)
			dat[p.x * WIDTH + p.y++] = color;
		p.x++;
	}
}

void	calculate_transform(t_fdf *fdf, double rot[4][4], double project[4][4])
{
	project[0][0] *= fdf->scale;
	project[1][1] *= fdf->scale;
	project[2][2] *= fdf->scale;
	project[2][2] *= fdf->del;
	concat_matrix(rot, project, project);
}

void	draw(t_fdf *fdf, t_map *map)
{
	t_point *vertex;
	int		i;

	i = 0;
	vertex = fdf->vertex;
	fill(fdf, new_point(0, 0, 0, NULL), HEIGHT, WIDTH);
	calculate_transform(fdf, fdf->rotation, fdf->project);
	while (i < map->size)
	{
		if (i % map->y_max < map->y_max - 1)
			draw_line(fdf, project(fdf, fdf->project, vertex[i]),
					project(fdf, fdf->project, vertex[i + 1]));
		if (i < map->size - map->y_max)
			draw_line(fdf, project(fdf, fdf->project, vertex[i]),
					project(fdf, fdf->project, vertex[i + map->y_max]));
		i++;
	}
	diagonalize(fdf->project, 1.0);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
