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

static int	close_window(void *param);

int 		keyborad(int key, void	*param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	if (key == 123 || key == 124 || key == 125 || key == 126)
		move(fdf, key);
	if (key == 34)
//		fdf->project = 1;
		printf("SET ISO\n");
	if (key == 53)
		close_window(fdf);
	if (key == 6)
		fdf->view->gamma = (fdf->view->gamma + 5) % 360;
	if (key == 7)
		fdf->view->alpha = (fdf->view->alpha + 5) % 360;
	if (key == 16)
		fdf->view->beta = (fdf->view->beta + 5) % 360;
	if (key == 69)
		fdf->view->scale -= fdf->view->scale == 1 ?  0.01f : 1;
	if (key == 24)
		fdf->view->eye[2] += 1;
	if (key == 27)
		fdf->view->eye[2] -= 1;
	draw(fdf, fdf->map);
	return (1);
}

static int	mouse_press(int key, int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf  = (t_fdf*)param;
	if (key == 1 || key == 2)
		printf("(x: %d, y: %d)\n", x, y);
	if (key == 4 || key == 5)
		zoom(fdf, key);
	draw(fdf, fdf->map);
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