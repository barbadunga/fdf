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
	printf("KEY PRESSED - [%d]\n", key);
	param += 0;
	return (1);
}
static int	mouse_press(int key, int x, int y, void *param)
{
	t_point	p;
	t_point	p0;
	t_fdf	*fdf;

	fdf  = (t_fdf*)param;
	p.x = x;
	p.y = y;
	p0.x = WIDTH;
	p0.y = HEIGHT;
	p.color = 0xFF0000;
	if (key == 1)
		draw_line(fdf, p0, p);
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
	mlx_hook(fdf->win, EXIT_BUTTON, 1L << 17, close_window, fdf);
	mlx_hook(fdf->win, 2, 0, keyborad, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
}