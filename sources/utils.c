/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:28:48 by mshagga           #+#    #+#             */
/*   Updated: 2019/09/13 13:10:16 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	sort_points(t_point *p0, t_point *p1, t_point *p2)
{
	if (p0->y == p1->y && p0->y == p2->y)
		return ;
	if (p0->y > p1->y)
		swap_points(p0, p1);
	if (p0->y > p2->y)
		swap_points(p0, p2);
	if (p1->y > p2->y)
		swap_points(p1, p2);
}

void	swap_points(t_point *p1, t_point *p2)
{
	t_point	tmp;

	tmp.x = p2->x;
	tmp.y = p2->y;
	tmp.z = p2->z;
	tmp.color = p2->color;
	p2->x = p1->x;
	p2->y = p1->y;
	p2->z = p1->z;
	p2->color = p1->color;
	p1->x = tmp.x;
	p1->y = tmp.y;
	p1->z = tmp.z;
	p1->color = tmp.color;
}

size_t	get_hex(char *hex)
{
	uint32_t	val;
	uint8_t		byte;

	val = 0;
	byte = 0;
	if (!(hex = ft_strchr(hex, 'x')))
		return (0);
	while (*hex++)
	{
		if (ft_isdigit(*hex))
			byte = *hex - '0';
		else if (*hex >= 'a' && *hex <= 'z')
			byte = *hex - 'a' + 10;
		else if (*hex >= 'A' && *hex <= 'Z')
			byte = *hex - 'A' + 10;
		val = (val << 4u) | byte;
	}
	return ((size_t)val >> 4u);
}

void	diagonalize(double matrix[4][4], double value)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				matrix[i][j] = value;
			else
				matrix[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

void	mtrxcpy(double src[4][4], double dest[4][4])
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dest[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}
