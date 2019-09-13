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

void	move(t_fdf *fdf, int key)
{
	if (key == 123)
		fdf->translate[1] -= 5;
	if (key == 124)
		fdf->translate[1] += 5;
	if (key == 125)
		fdf->translate[0] += 5;
	if (key == 126)
		fdf->translate[0] -= 5;
}

void	rotate(t_fdf *fdf, int key)
{
	if (key == 0)
		x_rotation(fdf->rotation, ROTATE_3);
	if (key == 2)
		x_rotation(fdf->rotation, -ROTATE_3);
	if (key == 1)
		y_rotation(fdf->rotation, ROTATE_3);
	if (key == 13)
		y_rotation(fdf->rotation, -ROTATE_3);
	if (key == 12)
		z_rotation(fdf->rotation, ROTATE_3);
	if (key == 14)
		z_rotation(fdf->rotation, -ROTATE_3);
}

void	scale(t_fdf *fdf, int key)
{
	if (key == 47)
		fdf->del += 0.1;
	else if (key == 43)
		fdf->del -= fdf->del < 0.1 ? 0.0 : 0.1;
}
