/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:47:06 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/26 23:55:49 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vec3	rotate(t_vec3 vec, t_vec3 rot)
{
	double	tempo;

	rot.x *= (M_PI / 180);
	rot.y *= (M_PI / 180);
	rot.z *= (M_PI / 180);
	tempo = vec.y;
	vec.y = vec.y * cos(rot.x) - vec.z * sin(rot.x);
	vec.z = tempo * sin(rot.x) + vec.z * cos(rot.x);
	tempo = vec.x;
	vec.x = vec.x * cos(rot.y) + vec.z * sin(rot.y);
	vec.z = vec.z * cos(rot.y) - tempo * sin(rot.y);
	tempo = vec.x;
	vec.x = vec.x * cos(rot.z) - vec.y * sin(rot.z);
	vec.y = tempo * sin(rot.z) + vec.y * cos(rot.z);
	return (vec);
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
	a->d.camera_rot = get_vector(fd);
	get_cones(a, fd);
	get_planes(a, fd);
	get_spheres(a, fd);
	get_cylinders(a, fd);
	get_light(a, fd);
}
