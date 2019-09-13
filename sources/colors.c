/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:41:18 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/08/17 20:41:18 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		linear_gradient(unsigned int start, double position, unsigned int end)
{
	int		rgb[3];
	int		i;
	int		shift;

	i = 0;
	shift = 0;
	while (i < 3)
	{
		rgb[i] = (int)((1.0 - position) * (start >> shift & 0xFF)
						+ position * (end >> shift & 0xFF));
		i++;
		shift += 8;
	}
	return (rgb[2] << 16 | rgb[1] << 8 | rgb[0]);
}

void	colorize(t_fdf *fdf)
{
	int		i;
	t_point	*p;

	i = 0;
	while (i < fdf->map->size)
	{
		p = fdf->vertex + i;
		if (p->z < (fdf->map->z_max - fdf->map->z_min) / 4)
			p->color = BOTTOM;
		else if (p->z > ((fdf->map->z_max - fdf->map->z_min) * 3) / 4)
			p->color = TOP;
		else
			p->color = MID;
		i++;
	}
}
