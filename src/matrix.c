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

void	identity(double matrix[4][4])
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
				matrix[i][j] = 1.0;
			else
				matrix[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

void		concat_matrix(double m1[4][4], double m2[4][4], double res[4][4])
{
	int	i;
	int	j;
	int k;


	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				res[i][j] += m1[i][k] * m2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

void		xrotate(double matrix[4][4], double angle)
{
	const double	cosinus = cos(angle);
	const double	sinus = sin(angle);
	double			rot[4][4];

	identity(rot);
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

	identity(rot);
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

	identity(rot);
	rot[0][0] = cosinus;
	rot[0][1] = -sinus;
	rot[1][0] = sinus;
	rot[1][1] = cosinus;
	concat_matrix(rot, matrix, matrix);
}

void		rotate(double res[4][4], double alpha, double beta, double gamma)
{
	double	tmp[4][4];

	identity(tmp);
	xrotate(tmp, alpha);
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
//	printf("x: %f y: %f z: %f\n", res3d[0], res3d[1], res3d[2]);
	vertex.x = ((int)(res3d[0] / res3d[3] * PROJECT_RATIO * (WIDTH / 2.0f) + 0.5)) + WIDTH / 2;
	vertex.y = ((int)(res3d[1] / res3d[3] * PROJECT_RATIO * (HEIGHT / 2.0f) + 0.5)) + HEIGHT / 2;
	return (vertex);
}

