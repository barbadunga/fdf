/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:32:11 by mshagga           #+#    #+#             */
/*   Updated: 2019/08/14 14:32:11 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	move(t_fdf *fdf, int key)
{
	if (key == 123)
		fdf->view->y_offset -= 5;
	if (key == 124)
		fdf->view->y_offset += 5;
	if (key == 125)
		fdf->view->x_offset += 5;
	if (key == 126)
		fdf->view->x_offset -= 5;
}

void 	zoom(t_fdf *fdf, int key)
{
	if (key == 4)
		fdf->view->scale += 0.2f;
	if (key == 5)
		fdf->view->scale -= fdf->view->scale <= 0 ? 0 : 0.2f;
}

void	rotate_z(t_fdf *fdf, t_point *vertex)
{
	const double	angle = DEG2RAD(fdf->view->gamma);
	const int		x = vertex->x;
	const int		y = vertex->y;

	vertex->y = (int)(x * sin(angle) + y * cos(angle));
	vertex->x = (int)(x * cos(angle) - y * sin(angle));
}

void	rotate_y(t_fdf *fdf, t_point *vertex)
{
	const double	angle = DEG2RAD(fdf->view->beta);
	const int	x = vertex->x;
	const int	z = vertex->z;

	vertex->x = (int)(x * cos(angle) + z * sin(angle));
	vertex->z = (int)(-x * sin(angle) + z * cos(angle));
}

void	rotate_x(t_fdf *fdf, t_point *vertex)
{
	const double	angle = DEG2RAD(fdf->view->alpha);
	const int	y = vertex->y;
	const int	z = vertex->z;

	vertex->y = (int)(y * cos(angle) + z * sin(angle));
	vertex->z = (int)(-y * sin(angle) + z * cos(angle));
}