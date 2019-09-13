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

void	draw_menu(t_fdf *fdf)
{
	void		*mlx;
	void		*win;
	const int	center = WIDTH / 10;
	const int	shift = center - center / 2 - 30;

	mlx = fdf->mlx;
	win = fdf->win;
	mlx_string_put(mlx, win, center - 40, 0, 0xA45B5B, "Rotate:");
	mlx_string_put(mlx, win, shift, 60, 0xFFFFFF, "Y axis: W | S");
	mlx_string_put(mlx, win, shift, 100, 0xFFFFFF, "X axis: A | D");
	mlx_string_put(mlx, win, shift, 140, 0xFFFFFF, "Z axis: Q | E");
	mlx_string_put(mlx, win, center - 30, 200, 0xA45B5B, "Zoom:");
	mlx_string_put(mlx, win, shift, 260, 0xFFFFFF, "In/Out: + | -");
	mlx_string_put(mlx, win, shift, 300, 0xFFFFFF, "Scale: < | >");
	mlx_string_put(mlx, win, center - 55, 360, 0xA45B5B, "Projection:");
	mlx_string_put(mlx, win, shift, 420, 0xFFFFFF, "Isometric: I");
	mlx_string_put(mlx, win, shift, 460, 0xFFFFFF, "Projection: P");
	mlx_string_put(mlx, win, shift, 500, 0xFFFFFF, "Change color: C");
	mlx_string_put(mlx, win, center - 30, 560, 0xA45B5B, "Move:");
	mlx_string_put(mlx, win, shift, 620, 0xFFFFFF, "On arrows");
}

void	fill(t_fdf *fdf, t_point p, int height, int width)
{
	int			*dat;
	int			start;

	start = p.y;
	dat = (int *)fdf->data;
	height += p.x;
	width += p.y;
	while (p.x < height && p.x < HEIGHT)
	{
		p.y = start;
		while (p.y < width && p.y < WIDTH)
			dat[p.x * WIDTH + p.y++] = p.color;
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
	fdf->project[3][2] = -1 / 2.0;
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
	fill(fdf, new_point(0, 0, 0, 0), HEIGHT, WIDTH);
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
	fill(fdf, new_point(0, 0, 0, 0x2F2F2F), HEIGHT, WIDTH / 5);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	draw_menu(fdf);
}
