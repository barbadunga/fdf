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

void	print_vec(t_vec *vec)
{
	int	i;
	int j;

	while (i < vec->total)
	{
		while (j < ((t_vec*)vec->data)->total)
		{

		}
	}
}

int		main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_vec	*map;

	if (argc != 2)
		return (-1);
	if (!(map = read_map(argv[1])))
		return (0);
	fdf = fdf_init();
	print_vec(map);
	event_handler(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}