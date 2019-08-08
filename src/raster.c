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

t_point	new_point(int x, int y, int z, int color)
{
	t_point p;

	p.x = x * 20 + 100;
	p.y = y * 20 + 50;
	ft_putnbr(z);
	if (z != 0)
		color = 0x0000FF;
	p.z = z * 20 + 100;
	p.color = color;
	return (p);
}

void	draw(t_fdf *fdf, t_map *map)
{
	t_point	current;
	int		i;
	int		j;

	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			current = new_point(i, j, map->plane[i][j], 0xFF0000);
			draw_line(fdf, current, new_point(i + 1, j, map->plane[i][j], current.color));
			draw_line(fdf, current, new_point(i, j + 1, map->plane[i][j], current.color));
			j++;
		}
		i++;
	}
}