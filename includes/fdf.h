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
# include <limits.h>
#include <math.h>

# define DEG2RAD(f) f * 3.14 / 180
# define ROTATE_3 M_PI / 90
# define EXIT_BUTTON 17
# define WIDTH 1920
# define HEIGHT 1080

typedef struct	s_point
{
	int		x;
	int 	y;
	int		z;
	int		norm;
	int 	color;
}				t_point;

typedef struct	s_map
{
	int		**plane;
	int 	x_max;
	int 	y_max;
	int		z_max;
	int		size;
}				t_map;

typedef struct	s_fdf
{
	t_map	*map;
	t_point *vertex;
	int		*z_buffer;
	double	project[4][4];
	double	rotation[4][4];
	int		translate[3];
	double	scale;
	void	*win;
	void	*mlx;
	void	*img;
	char	*data;
	int		size_line;
	int		bpp;
	int 	end;
}				t_fdf;

void		draw_line(t_fdf *fdf, t_point p0, t_point p1);

t_fdf		*fdf_init(t_map **map);
void		event_handler(t_fdf *fdf);
t_map		*read_map(char *filename);
void		draw(t_fdf *fdf, t_map *map);
void		fill(t_fdf *fdf, int x, int y, int height, int width, int color);
t_point		project(t_fdf *fdf, double matrix[4][4], t_point vertex);
t_point		new_point(int x, int y, int z, int color);
void		img_pixel_put(t_fdf	**fdf, t_point	pixel);

/*
 * Controls funcs
 */

void	zoom(t_fdf *fdf, int key);
void 	move(t_fdf *fdf, int key);
void		x_rotation(double rot[4][4], double angle);
void		y_rotation(double rot[4][4], double angle);
void		z_rotation(double rot[4][4], double angle);

/*
 * Matrix
 */

void		concat_matrix(double m1[4][4], double m2[4][4], double res[4][4]);
void		identity(double matrix[4][4], double value);
void		print(double matrix[4][4]);

#endif