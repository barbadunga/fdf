/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:50:46 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/08/01 14:50:46 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdio.h>

//t_vec		*get_data(int fd)
//{
//	t_vec	*raw_data;
//	char	buff[1];
//
//	if (read(fd, NULL, 0) < 0 || !(raw_data = ft_vec_init(2, sizeof(char))))
//		return (NULL);
//	while (read(fd, buff, 1) > 0)
//		ft_vec_add(&raw_data, buff);
//	ft_vec_add(&raw_data, "\0");
//	ft_putstr(raw_data->data);
//	return (raw_data);
//}

//int			*ft_split(char	*line)
//{
//	int		*arr;
//	int		counter;
//	char	*ptr;
//
//	ptr = line;
//	counter = 0;
//	while (*ptr)
//	{
//		while (ft_isdigit(*ptr))
//			ptr++;
//		counter++;
//		while (ft_isspace(*ptr))
//			ptr++;
//	}
//	if (!(arr = (int*)malloc(sizeof(int) * counter)))
//		return (NULL);
//	counter = 0;
//	while (*line)
//	{
//		arr[counter++] = ft_atoi(line);
//		while (ft_isdigit(*line))
//			line++;
//		while (ft_isspace(*line))
//			line++;
//	}
//	return (arr);
//}

t_vec	*ft_split(char *line)
{
	t_vec	*arr;
	int		val;

	if (!(arr = ft_vec_init(2, sizeof(int))))
		return (NULL);
	while (*line)
	{
		val = ft_atoi(line);
		ft_vec_add(&arr, &val);
		while (ft_isdigit(*line))
			line++;
		while (ft_isspace(*line))
			line++;
	}
	ft_vec_resize(&arr);
	return (arr);
}

t_vec	*read_map(char *filename)
{
	t_vec	*map;
	char	*line;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	if (!(map = ft_vec_init(2, sizeof(t_vec*))))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
		ft_vec_add(&map, ft_split(line));
	ft_vec_resize(&map);
	return (map);
}