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

static void	img_pixel_put(t_fdf	**fdf, t_point	pixel)
{
	unsigned int	color;
	int				i;

	color = mlx_get_color_value((*fdf)->mlx, pixel.color);
	i = (pixel.y * (*fdf)->bpp / 8) + (pixel.x * (*fdf)->size_line);
	if (i >= 0)
	{
		(*fdf)->data[i] = color;
		(*fdf)->data[++i] = color >> (unsigned)8;
		(*fdf)->data[++i] = color >> (unsigned)16;
		(*fdf)->data[++i] = 0;
	}
}

static void octant1(t_fdf *fdf, t_point p0, int dx, int dy, int dir)
{
	int dXx2;
	int dXx2_dYx2;
	int error;

	dXx2 =  dx * 2;
	dXx2_dYx2 = dXx2 - dy * 2;
	error = dXx2 - dy;
	img_pixel_put(&fdf, p0);
	while ( dy-- ) {
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

static void	octant0(t_fdf *fdf, t_point p0, int dx, int dy, int dir)
{
	const int	dy_x2 = dy * 2;
	const int	dy_x2_minus_dx_x2 = dy_x2 - dx * 2;
	int			err;

	err = dy_x2 - dx;
	img_pixel_put(&fdf, p0);
	while (dx--)
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
	int	tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void		draw_line(t_fdf *fdf, t_point p0, t_point p1)
{
	int		d_x;
	int 	d_y;

	if (p0.y > p1.y)
	{
		ft_swap(&p0.y, &p1.y);
		ft_swap(&p0.x, &p1.x);
	}
	d_x = p1.x - p0.x;
	d_y = p1.y - p0.y;
	if (d_x > 0)
		d_x > d_y ? octant0(fdf, p0, d_x, d_y, 1) : octant1(fdf, p0, d_x, d_y, 1);
	else
	{

		d_x = -d_x;
		d_x > d_y ? octant0(fdf, p0, d_x, d_y, -1) : octant1(fdf, p0, d_x, d_y, -1);
	}
}