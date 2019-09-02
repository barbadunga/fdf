/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:39:23 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/08/01 16:39:23 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	img_pixel_put(t_fdf	**fdf, t_point	pixel)
{
	unsigned int	color;
	int				i;

	color = mlx_get_color_value((*fdf)->mlx, pixel.color);
	i = (pixel.y * (*fdf)->bpp / 8) + (pixel.x * (*fdf)->size_line);
	if (i >= 0 && pixel.x > 0 && pixel.x < HEIGHT && pixel.y > 0 && pixel.y < WIDTH)
	{
		(*fdf)->data[i] = color;
		(*fdf)->data[++i] = color >> (unsigned)8;
		(*fdf)->data[++i] = color >> (unsigned)16;
		(*fdf)->data[++i] = 0;
	}
}

static void octant1(t_fdf *fdf, t_point p0, t_point delta, int dir)
{
	const int		dXx2 = delta.x * 2;
	const int		dXx2_dYx2 = dXx2 - delta.y * 2;
	int				error;

	error = dXx2 - delta.y;
	img_pixel_put(&fdf, p0);
	while (delta.y--)
	{
		if ( error >= 0 )
		{
			p0.x += dir;
			error += dXx2_dYx2;
		}
		else
			error += dXx2;
		p0.y++;
		img_pixel_put(&fdf, p0);
	}
}

static void	octant0(t_fdf *fdf, t_point p0, t_point delta, int dir)
{
	const int		dy_x2 = delta.y * 2;
	const int		dy_x2_minus_dx_x2 = dy_x2 - delta.x * 2;
	int				err;

	err = dy_x2 - delta.x;
	img_pixel_put(&fdf, p0);
	while (delta.x--)
	{
		if (err >= 0)
		{
			p0.y++;
			err += dy_x2_minus_dx_x2;
		}
		else
			err += dy_x2;
		p0.x += dir;
		img_pixel_put(&fdf, p0);
	}
}

void		ft_swap(int *p1, int *p2)
{
	int tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void		draw_line(t_fdf *fdf, t_point p0, t_point p1)
{
	t_point	delta;

	if (p0.y > p1.y)
	{
		ft_swap(&p0.x, &p1.x);
		ft_swap(&p0.y, &p1.y);
		ft_swap(&p0.z, &p1.z);
		ft_swap(&p0.color, &p1.color);
	}
	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	delta.z = p1.z - p0.z;
	delta.color = p1.color;
	if (delta.x > 0)
		delta.x > delta.y ? octant0(fdf, p0, delta, 1) : octant1(fdf, p0, delta, 1);
	else
	{

		delta.x = -delta.x;
		delta.x > delta.y ? octant0(fdf, p0, delta, -1) : octant1(fdf, p0, delta, -1);
	}
}