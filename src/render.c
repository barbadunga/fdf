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

t_point	*project_vertex(t_fdf *fdf, int size)
{
	t_point	*projected;
	int		i;

	if (!(projected = (t_point*)malloc(sizeof(t_point) * size)))
		return (NULL);
	fdf->project[0][0] *= fdf->scale;
	fdf->project[1][1] *= fdf->scale;
	fdf->project[2][2] *= fdf->scale;
	fdf->project[2][2] *= fdf->del;
	concat_matrix(fdf->rotation, fdf->project, fdf->project);
	i = 0;
	while (i < size)
	{
		projected[i] = project(fdf, fdf->project, fdf->vertex[i]);
		i++;
	}
	return (projected);
}

void	draw(t_fdf *fdf, t_map *map)
{
	t_point	*projected;
	int		i;

	i = 0;
	fill(fdf, new_point(0, 0, 0, NULL), HEIGHT, WIDTH);
	projected = project_vertex(fdf, fdf->map->size);
	while (i < map->size)
	{
		if (i % map->y_max < map->y_max - 1)
			draw_line(fdf, projected[i], projected[i + 1]);
		if (i < map->size - map->y_max)
			draw_line(fdf, projected[i], projected[i + map->y_max]);
		i++;
	}
	free(projected);
	diagonalize(fdf->project, 1.0);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
