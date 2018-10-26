/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:47:06 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/26 15:43:36 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vec3	get_rot(int fd, t_vec3 vec)
{
	t_vec3	rot;

	rot = get_vector(fd);
	rot.x *= (M_PI / 180);
	rot.y *= (M_PI / 180);
	rot.z *= (M_PI / 180);
	return (rotate(vec, rot));
}

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
	return (integer < 0 ? -integer : integer);
}

double	get_double(int fd)
{
	double	res;
	char	*line;
	char	*dot;

	if (!get_next_line(fd, &line))
	{
		fprintf(stderr, "Incomplete data!");
		exit(-1);
	}
	res = (double)ft_atoi(line);
	dot = ft_strchr(line, '.');
	if (dot)
		if (*(++dot) != '\0')
		{
			if (res < 0)
				res -= ft_atoi(dot) / pow(10, ft_strlen(dot));
			else
				res += ft_atoi(dot) / pow(10, ft_strlen(dot));
		}
	free(line);
	return (res);
}

t_vec3	get_vector(int fd)
{
	t_vec3	vec;

	vec.x = get_double(fd);
	vec.y = get_double(fd);
	vec.z = get_double(fd);
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
	a->d.camera_dir = get_rot(fd, a->d.camera_dir);
	get_cones(a, fd);
	get_planes(a, fd);
	get_spheres(a, fd);
	get_cylinders(a, fd);
	get_light(a, fd);
}
