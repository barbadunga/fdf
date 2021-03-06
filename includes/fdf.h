/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 11:32:23 by mshagga           #+#    #+#             */
/*   Updated: 2019/09/13 12:26:20 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "mlx.h"
# include <stdlib.h>
# include "libft.h"
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

# define BOTTOM			0x00416A
# define TOP			0xFFE000
# define MID			0x799F0C

# define DEG2RAD(f)		f * 3.14 / 180
# define ROTATE_3		M_PI / 90
# define EXIT_BUTTON	17
# define WIDTH			1440
# define HEIGHT			900

typedef struct	s_point
{
	int	x;
	int y;
	int	z;
	int color;
}				t_point;

typedef struct	s_map
{
	size_t	**mesh;
	int		x_max;
	int		y_max;
	int		z_max;
	int		z_min;
	int		size;
}				t_map;

typedef struct	s_fdf
{
	t_map	*map;
	t_point	*vertex;
	int		*zbuffer;
	double	project[4][4];
	double	rotation[4][4];
	int		translate[3];
	double	del;
	double	scale;
	void	*win;
	void	*mlx;
	void	*img;
	char	*data;
	int		size_line;
	int		bpp;
	int		end;
}				t_fdf;

t_fdf		*fdf_init(t_map **map);
void		event_handler(t_fdf *fdf);
t_map		*read_map(char *filename);
void		draw(t_fdf *fdf, t_map *map);
void		fill(t_fdf *fdf, t_point p, int height, int width);
t_point		project(t_fdf *fdf, double matrix[4][4], t_point vertex);
void		img_pixel_put(t_fdf **fdf, t_point pixel);

void		swap_points(t_point *p1, t_point *p2);
void		sort_points(t_point	*p0, t_point *p1, t_point *p2);
void		draw_line(t_fdf *fdf, t_point p0, t_point p1);
t_point		new_point(int x, int y, int z, int color);
size_t		get_hex(char *hex);

void		move(t_fdf *fdf, int key);
void		rotate(t_fdf *fdf, int key);
void		scale(t_fdf *fdf, int key);
void		x_rotation(double rot[4][4], double angle);
void		y_rotation(double rot[4][4], double angle);
void		z_rotation(double rot[4][4], double angle);
int			close_window(void *param);

void		concat_matrix(double m1[4][4], double m2[4][4], double res[4][4]);
void		diagonalize(double matrix[4][4], double value);
void		mtrxcpy(double src[4][4], double dest[4][4]);

int			linear_gradient(unsigned int start, double position,
							unsigned int end);
void		colorize(t_fdf *fdf);

#endif
