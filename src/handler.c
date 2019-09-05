/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:33:37 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/08/01 13:33:37 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void		colorize(t_fdf *fdf)
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

void		parallel(t_fdf *fdf)
{
	int i;

	i = 0;
	fdf->scale = 1.0;
	identity(fdf->rotation, 1.0);
	identity(fdf->project, 1.0);
	while (i < 3)
		fdf->translate[i++] = 0;
}

void		isometric(t_fdf *fdf)
{
	int i;

	i = 0;
	fdf->scale = 1.0;
	identity(fdf->rotation, 1.0);
	y_rotation(fdf->rotation, DEG2RAD(45));
	z_rotation(fdf->rotation, DEG2RAD(30));
	while (i < 3)
		fdf->translate[i++] = 0;
}

int 		keyborad(int key, void	*param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	if (key == 8)
		colorize(fdf);
	if (key == 123 || key == 124 || key == 125 || key == 126)
		move(fdf, key);
	if (key == 35)
		parallel(fdf);
	if (key == 34)
		isometric(fdf);
	if (key == 53)
		close_window(fdf);
	if (key == 43 || key == 47)
		scale(fdf, key);
	if (key == 0 || key == 2 || key == 1 || key == 13 || key == 12 || key == 14)
		rotate(fdf, key);
	if (key == 24)
		fdf->scale += 0.1f;
	if (key == 27)
		fdf->scale -= fdf->scale > 0.2 ? 0.1f : 0.0;
	draw(fdf, fdf->map);
	return (1);
}

int			close_window(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
}

void		event_handler(t_fdf *fdf)
{
	mlx_hook(fdf->win, EXIT_BUTTON, 1LU << (unsigned)17, close_window, fdf);
	mlx_hook(fdf->win, 2, 0, keyborad, fdf);
}
