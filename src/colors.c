/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 20:41:18 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/08/17 20:41:18 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		linear_gradient(unsigned int start, double position, unsigned int end)
{
	int		rgb[3];
	int		i;
	int		shift;

	i = 0;
	shift = 0;
	while (i < 3)
	{
		rgb[i] = (int)((1.0 - position) * (start >> shift & 0xFF)
						+ position * (end >> shift & 0xFF));
		i++;
		shift += 8;
	}
	return (rgb[2] << 16 | rgb[1] << 8 | rgb[0]);
}
