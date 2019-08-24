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

void	img_pixel_put(t_fdf	**fdf, t_point	pixel)
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

int			check_depth_y(t_point s, t_point c, t_point e)
{
	t_point	point;
	double	z_val;
	double tmp[3];
	double	k;

	k = e.y == s.y? 1.0 : (double)(c.y - s.y) / (double)(e.y - s.y);
	point = new_point(e.x - s.x, e.y - s.y, e.z - s.z, s.color);
	tmp[0] = point.x * k + s.x;
	tmp[1] = point.y * k + s.y;
	z_val = point.z * k + s.z;
	return ((int)(z_val));
}

static void octant1(t_fdf *fdf, t_point p0, int dx, int dy, int dir, t_point end)
{
	int dXx2;
	t_point	start = p0;
	int z_val;
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
		if ((z_val = check_depth_y(start, p0, end)) >= fdf->z_buffer[p0.x + p0.y * fdf->map->y_max])
		{
			fdf->z_buffer[p0.x + p0.y * fdf->map->y_max] = z_val;
			img_pixel_put(&fdf, p0);
		}
	}
}

int			check_depth_x(t_point s, t_point c, t_point e)
{
	t_point	point;
	double	z_val;
	double tmp[3];
	double	k;

	k = e.x == s.x ? 1.0 : (double)(c.x - s.x) / (double)(e.x - s.x);
	point = new_point(e.x - s.x, e.y - s.y, e.z - s.z, s.color);
	tmp[0] = point.x * k + s.x;
	tmp[1] = point.y * k + s.y;
	z_val = point.z * k + s.z;
	return ((int)(z_val));
}

static void	octant0(t_fdf *fdf, t_point p0, int dx, int dy, int dir, t_point end)
{
//	const t_point	start = p0;
	end.x++;
	const int		dy_x2 = dy * 2;
	const int		dy_x2_minus_dx_x2 = dy_x2 - dx * 2;
//	int				z_val;
	int				err;

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
//		if ((z_val = check_depth_x(start, p0, end)) >= fdf->z_buffer[p0.x + p0.y * fdf->map->y_max])
//		{
//			fdf->z_buffer[p0.x + p0.y * fdf->map->y_max] = z_val;
			img_pixel_put(&fdf, p0);
//		}
	}
}

void		swap_points(t_point *p1, t_point *p2)
{
	t_point	tmp;

	tmp.x = p1->x;
	tmp.y = p1->y;
	tmp.z = p1->z;
	tmp.color = p1->color;
	p2->x = tmp.x;
	p2->y = tmp.y;
	p2->z = tmp.z;
	p2->color = tmp.color;
}

void		draw_line(t_fdf *fdf, t_point p0, t_point p1)
{
	int		d_x;
	int 	d_y;

	if (p0.y > p1.y)
		swap_points(&p0, &p1);
	d_x = p1.x - p0.x;
	d_y = p1.y - p0.y;
	if (d_x > 0)
		d_x > d_y ? octant0(fdf, p0, d_x, d_y, 1, p1) : octant1(fdf, p0, d_x, d_y, 1, p1);
	else
	{
		d_x = -d_x;
		d_x > d_y ? octant0(fdf, p0, d_x, d_y, -1, p1) : octant1(fdf, p0, d_x, d_y, -1, p1);
	}
}