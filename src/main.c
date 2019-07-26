/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:53:16 by mshagga           #+#    #+#             */
/*   Updated: 2019/07/25 16:53:27 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include <stdio.h>

int		draw_pixel(int button, int x, int y, void *param)
{
	t_fdf	*fdf;
	int		i;

	i = 0;
	fdf = (t_fdf*)param;
	printf("x = %d\ty = %d\t%d\n", x, y, button);
	if (x >= 0 && y >= 0 && x <= fdf->x && y <= fdf->y && button == 1)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, x, y, 255);
		ft_vec_add(&(fdf->points), &x);
		ft_vec_add(&(fdf->points), &y);
	}

	return (0);
}

int		close_fdf(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(1);
}
/*
 * If not allocated then delete all !!!!
 */

t_fdf	*init(int size_x, int size_y, char *title)
{
	t_fdf	*fdf;
	int 	i;

	i = 0;
	if (!(fdf = (t_fdf*)malloc(sizeof(t_fdf))))
		return (NULL);
	fdf->x = size_x;
	fdf->y = size_y;
	if (!(fdf->mlx = mlx_init()))
		return (NULL);
	if (!(fdf->win = mlx_new_window(fdf->mlx, fdf->x, fdf->y, title)))
		return (NULL);
	if (!(fdf->space = (int**)malloc(sizeof(int*) * fdf->x)))
		return (NULL);
	while (i <= fdf->y)
		if (!(fdf->space[i++] = (int*)malloc(sizeof(int) * fdf->y)))
			return (NULL);
	if (!(fdf->points = ft_vec_init(10, sizeof(int))))
		return (NULL);
	return (fdf);
}

int		main(void)
{
	t_fdf	*fdf;

	if (!(fdf = init(640, 480, "Untitled")))
		return (-1);
	mlx_hook(fdf->win, 4, 1L<< 0, draw_pixel, fdf);
	mlx_hook(fdf->win, 17, 1L << 17, close_fdf, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}