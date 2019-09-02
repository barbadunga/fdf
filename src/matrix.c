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

void		x_rotation(double rot[4][4], double angle)
{
	int				i;
	double			tmp[3][3];
	const double	sinus = sin(angle);
	const double	cosinus = cos(angle);

	i = 0;
	while (i < 3)
	{
		tmp[1][i] = cosinus * rot[1][i] + -sinus * rot[2][i];
		tmp[2][i] = sinus * rot[1][i] + cosinus * rot[2][i];
		i++;
	}
	i = 0;
	while (i < 3)
	{
		rot[1][i] = tmp[1][i];
		rot[2][i] = tmp[2][i];
		i++;
	}
}

void		y_rotation(double rot[4][4], double angle)
{
	int				i;
	double			tmp[3][3];
	const double	sinus = sin(angle);
	const double	cosinus = cos(angle);

	i = 0;
	while (i < 3)
	{
		tmp[0][i] = cosinus * rot[0][i] + sinus * rot[2][i];
		tmp[2][i] = -sinus * rot[0][i] + cosinus * rot[2][i];
		i++;
	}
	i = 0;
	while (i < 3)
	{
		rot[0][i] = tmp[0][i];
		rot[2][i] = tmp[2][i];
		i++;
	}
}

void		z_rotation(double rot[4][4], double angle)
{
	int				i;
	double			tmp[4][4];
	const double	sinus = sin(angle);
	const double	cosinus = cos(angle);

	i = 0;
	while (i < 3)
	{
		tmp[0][i] = cosinus * rot[0][i] + -sinus * rot[1][i];
		tmp[1][i] = sinus * rot[0][i] + cosinus * rot[1][i];
		i++;
	}
	i = 0;
	while (i < 3)
	{
		rot[0][i] = tmp[0][i];
		rot[1][i] = tmp[1][i];
		i++;
	}
}

t_point		project(t_fdf *fdf, double matrix[4][4], t_point vertex)
{
	double		vec3d[4];
	double		res3d[4];
	int		i;
	int		j;

	i = 0;
	vec3d[0] = (2.0 * vertex.x) / fdf->map->x_max - 1.0;
	vec3d[1] = (2.0 * vertex.y) / fdf->map->y_max - 1.0;
	vec3d[2] = (2.0 * vertex.z) / fdf->map->z_max - 1.0;
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
//	res3d[0] /= res3d[3];
//	res3d[1] /= res3d[3];
//	res3d[2] /= res3d[3];
//	vertex.x = (int)(res3d[0] / (res3d[2] ? res3d[2] : 1.0) * HEIGHT / 4.0 + HEIGHT / 2.0);
//	vertex.y = (int)(res3d[1] / (res3d[2] ? res3d[2] : 1.0) * WIDTH / 4.0 + WIDTH / 2.0);

	vertex.x = (int)(res3d[0] * HEIGHT / 4.0 + HEIGHT / 2.0);
	vertex.y = (int)(res3d[1] * WIDTH / 4.0 + WIDTH / 2.0);
	vertex.x += fdf->translate[0];
	vertex.y += fdf->translate[1];
	return (vertex);
}

