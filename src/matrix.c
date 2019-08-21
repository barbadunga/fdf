/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:24:26 by mshagga           #+#    #+#             */
/*   Updated: 2019/08/19 17:24:26 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	identity(double matrix[4][4], double value)
{
	int i;
	int j;

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

void		mtrxcpy(double src[4][4], double dest[4][4])
{
	int	i;
	int	j;

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

void		concat_matrix(double m1[4][4], double m2[4][4], double res[4][4])
{
	double	tmp[4][4];
	int		i;
	int		j;
	int		k;


	i = 0;
	identity(tmp, 0.0);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				tmp[i][j] += m1[i][k] * m2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	mtrxcpy(tmp, res);
}

void		xrotate(double matrix[4][4], double angle)
{
	const double	cosinus = cos(angle);
	const double	sinus = sin(angle);
	double			rot[4][4];

	identity(rot, 1.0);
	rot[1][1] = cosinus;
	rot[1][2] = -sinus;
	rot[2][1] = sinus;
	rot[2][2] = cosinus;
	concat_matrix(rot, matrix, matrix);
}

void		yrotate(double	matrix[4][4], double angle)
{
	const double	cosinus = cos(angle);
	const double	sinus = sin(angle);
	double			rot[4][4];

	identity(rot, 1.0);
	rot[0][0] = cosinus;
	rot[0][2] = sinus;
	rot[2][0] = -sinus;
	rot[2][2] = cosinus;
	concat_matrix(rot, matrix, matrix);
}

void		zrotate(double matrix[4][4], double angle)
{
	const double	cosinus = cos(angle);
	const double	sinus = sin(angle);
	double			rot[4][4];

	identity(rot, 1.0);
	rot[0][0] = cosinus;
	rot[0][1] = -sinus;
	rot[1][0] = sinus;
	rot[1][1] = cosinus;
	concat_matrix(rot, matrix, matrix);
}

t_point		project(double matrix[4][4], t_point vertex)
{
	double		vec3d[4];
	double		res3d[4];
	int		i;
	int		j;

	i = 0;
	vec3d[0] = vertex.x;
	vec3d[1] = vertex.y;
	vec3d[2] = vertex.z;
	vec3d[3] = 1;
	while (i < 4)
	{
		res3d[i] = 0;
		j = 0;
		while (j < 4)
		{
			res3d[i] += matrix[i][j] * vec3d[j];
			j++;
		}
		i++;
	}
	vertex.x = (int)(res3d[0] / res3d[3]);
	vertex.y = (int)(res3d[1] / res3d[3]);
	return (vertex);
}

