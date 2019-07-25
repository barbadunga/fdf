/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:53:16 by mshagga           #+#    #+#             */
/*   Updated: 2019/07/25 16:53:27 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minilibx_macos/mlx.h"
#include "../libft/libft.h"
#include <stdio.h>

typedef struct  s_map
{
    void    *win;
    void    *mlx;
}               t_map;

int draw_pixel(int button, int x, int y, void *param)
{
    mlx_pixel_put(((t_map*)param)->mlx, ((t_map*)param)->win, x, y, 200);
    printf("%d\n", button);
    return (0);
}

int main(void)
{
    void    *win_ptr;
    void    *mlx_ptr;
    t_map   *map;

    map = (t_map*)ft_memalloc(sizeof(t_map));
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 640, 480, "Untitled");
    map->mlx = mlx_ptr;
    map->win = win_ptr;
    mlx_hook(win_ptr, 6, 0, draw_pixel, map);
    mlx_loop(mlx_ptr);
    return (0);
}