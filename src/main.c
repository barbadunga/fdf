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

#include "fdf.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	double world2view[4][4];
	double transform[4][4];
	t_fdf	*fdf;
	t_map	*map;

	if (argc != 2)
		return (-1);
	if (!(map = read_map(argv[1])))
		return (-1);
	if (!(fdf = fdf_init(&map)))
		return (-1);
	identity(world2view);
	identity(transform);
	draw(fdf, map);
	event_handler(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}