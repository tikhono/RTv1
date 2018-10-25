/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:47:06 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/25 14:47:51 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		get_int(int fd)
{
	int		integer;
	char	*line;

	if (!get_next_line(fd, &line))
	{
		fprintf(stderr, "Incomplete data!");
		exit(-1);
	}
	integer = ft_atoi(line);
	free(line);
	return (integer);
}

double	get_double(int fd)
{
	double	res;
	char	*line;

	if (!get_next_line(fd, &line))
	{
		fprintf(stderr, "Incomplete data!");
		exit(-1);
	}
	res = (double)ft_atoi(line);
	return (res);
}

t_vec3	get_vector(int fd)
{
	t_vec3	vec;
	char	*line;

	if (!get_next_line(fd, &line))
	{
		fprintf(stderr, "Incomplete data!");
		exit(-1);
	}
	vec.x = (double)ft_atoi(line);
	if (!get_next_line(fd, &line))
	{
		fprintf(stderr, "Incomplete data!");
		exit(-1);
	}
	vec.y = (double)ft_atoi(line);
	if (!get_next_line(fd, &line))
	{
		fprintf(stderr, "Incomplete data!");
		exit(-1);
	}
	vec.z = (double)ft_atoi(line);
	free(line);
	return (vec);
}

void	parse(t_all *a)
{
	int		fd;

	fd = open(a->d.file, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open: %s\n", a->d.file);
		exit(-1);
	}
	a->d.camera_pos = get_vector(fd);
	a->d.camera_dir = get_vector(fd);
	get_cones(a, fd);
	get_planes(a, fd);
	get_spheres(a, fd);
	get_cylinders(a, fd);
	get_light(a, fd);
}
