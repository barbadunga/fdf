/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:32:11 by mshagga           #+#    #+#             */
/*   Updated: 2019/08/14 14:32:11 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	move(t_fdf *fdf, int key)
{
	if (key == 123)
		fdf->translate[1] -= 5;
	if (key == 124)
		fdf->translate[1] += 5;
	if (key == 125)
		fdf->translate[0] += 5;
	if (key == 126)
		fdf->translate[0] -= 5;
}

void 	zoom(t_fdf *fdf, int key)
{
	if (key == 4)
		fdf->translate[2] += 3;
	if (key == 5)
		fdf->translate[2] -= fdf->translate[2] <= 1 ? 3 : 0;
}
