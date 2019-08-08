/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 11:32:23 by mshagga           #+#    #+#             */
/*   Updated: 2019/07/26 11:32:25 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "mlx.h"
# include "libft.h"
# include <unistd.h>

# define ABS(n) (n > 0 ? n : -n)
# define EXIT_BUTTON 17
# define HEIGHT 640
# define WIDTH 480

typedef struct	s_point
{
	int		x;
	int 	y;
	int 	z;
	int 	color;
}				t_point;

typedef struct	s_map
{
	int		**plane;
	int 	n_rows;
	int 	n_cols;
}				t_map;

typedef struct	s_fdf
{
	void	*win;
	void	*mlx;
	void	*image;
	char	prev;
}				t_fdf;

void	draw_line(t_fdf *fdf, t_point p0, t_point p1);

t_fdf	*fdf_init();
void	event_handler(t_fdf *fdf);
t_map	*read_map(char *filename);
void	draw(t_fdf *fdf, t_map *map);

#endif