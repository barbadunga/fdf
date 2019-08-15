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
# define DEG2RAD(f) f * 3.14 / 180
# define EXIT_BUTTON 17
# define WIDTH 800
# define HEIGHT 800

typedef struct	s_point
{
	int		x;
	int 	y;
	int 	z;
	int 	color;
}				t_point;

typedef struct	s_view
{
	float	scale;
	int		x_offset;
	int		y_offset;
	int		alpha;
	int		beta;
	int		gamma;
}				t_view;

typedef struct	s_map
{
	int		**plane;
	int 	n_rows;
	int 	n_cols;
	int		size;
}				t_map;

typedef struct	s_fdf
{
	t_map	*map;
	t_view	*view;
	t_point *vertex;
	int		project;
	void	*win;
	void	*mlx;
	void	*img;
	char	*data;
	int		size_line;
	int		bpp;
	int 	end;
}				t_fdf;

void	draw_line(t_fdf *fdf, t_point p0, t_point p1);

t_fdf	*fdf_init(t_map **map);
void	event_handler(t_fdf *fdf);
t_map	*read_map(char *filename);
void	draw(t_fdf *fdf, t_map *map);
void	fill(t_fdf *fdf, int x, int y, int height, int width, int color);

/*
 * Controls funcs
 */

void	zoom(t_fdf *fdf, int key);
void 	move(t_fdf *fdf, int key);
void	rotate_z(t_fdf *fdf, t_point *vertex);
void	rotate_y(t_fdf *fdf, t_point *vertex);
void	rotate_x(t_fdf *fdf, t_point *vertex);

#endif