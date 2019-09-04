/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:32:19 by mshagga           #+#    #+#             */
/*   Updated: 2019/09/04 13:32:19 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rasterize(t_fdf *fdf, t_point p0, t_point p1, t_point p2)
{
	int		height;
	double	alpha;
	double	beta;
	int		a;
	int 	b;
	int		i;
	int 	j;

	i = 0;
	j = 0;
	sort_points(&p0, &p1, &p2);
	height = p2.y - p1.y;
	while (i < height)
	{
		int second_half = i > p1.y - p0.y || p1.y == p0.y;
		int	segment_height = second_half ? p2.y - p1.y : p1.y - p0.y;
		alpha = (double)i / height;
		beta = (double)(i - (second_half ? p1.y - p0.y : 0.0)) / segment_height;
		a = (int)(p0.x + (p2.x - p0.x) * alpha);
		b = (int)( second_half ? p1.x + (p2.x - p1.x) * beta : p0.x + (p1.x - p0.x) * beta);
		if (a > b)
		{
			int tmp = b;
			b = a;
			a = tmp;
		}
		j = a;
		while (j < b)
			img_pixel_put(&fdf, new_point(j++, p0.y + i, 0, fdf->map));
		i++;
	}
}
