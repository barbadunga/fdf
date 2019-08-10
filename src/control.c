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

int 		keyborad(int key, void	*param)
{
	t_fdf	*fdf;

	if (key > 0)
		fdf = (t_fdf*)param;
	return (1);
}

static int	mouse_press(int key, int x, int y, void *param)
{
	t_point	p;
	t_point	p0;
	t_fdf	*fdf;

	fdf  = (t_fdf*)param;
	p.x = y;
	p.y = x;
	p0.x = WIDTH / 2;
	p0.y = HEIGHT / 2;
	p.color = 0xFF0000;
	if (key == 1)
		draw_line(fdf, p0, p);
	if (key == 4 || key == 5)
		zoom(fdf, key);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (1);
}

static int	close_window(void *param)
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
	mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
}