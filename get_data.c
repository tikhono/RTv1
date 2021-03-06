/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:14 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/27 01:08:19 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	get_cones(t_all *all, int fd)
{
	int		count;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	double	d;

	count = get_int(fd);
	while (count > 0)
	{
		a = get_vector(fd);
		b = get_vector(fd);
		b = rotate(b, get_vector(fd));
		c = get_vector(fd);
		d = get_double(fd);
		d = tan(d * M_PI / 360);
		d = 1 + d * d;
		push_list(&all->d.obj_list, obj_cone_create(a, b, c, d));
		--count;
	}
}

void	get_planes(t_all *all, int fd)
{
	int		count;
	t_vec3	a;
	t_vec3	b;
	double	c;

	count = get_int(fd);
	while (count > 0)
	{
		a = get_vector(fd);
		a = rotate(a, get_vector(fd));
		b = get_vector(fd);
		c = get_double(fd);
		push_list(&all->d.obj_list, obj_plane_create(a, b, c));
		--count;
	}
}

void	get_spheres(t_all *all, int fd)
{
	int		count;
	t_vec3	a;
	t_vec3	b;
	double	c;

	count = get_int(fd);
	while (count > 0)
	{
		a = get_vector(fd);
		b = get_vector(fd);
		c = get_double(fd);
		push_list(&all->d.obj_list, obj_sphere_create(a, b, c));
		--count;
	}
}

void	get_cylinders(t_all *all, int fd)
{
	int		count;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	double	d;

	count = get_int(fd);
	while (count > 0)
	{
		a = get_vector(fd);
		b = get_vector(fd);
		b = rotate(b, get_vector(fd));
		c = get_vector(fd);
		d = get_double(fd);
		push_list(&all->d.obj_list, obj_cyli_create(a, b, c, d));
		--count;
	}
}

void	get_light(t_all *all, int fd)
{
	int		count;
	t_vec3	a;
	double	b;

	count = get_int(fd);
	all->d.light_arr_length = count;
	all->d.light = (t_light *)malloc(sizeof(t_light) * count);
	while (count > 0)
	{
		a = get_vector(fd);
		b = get_double(fd);
		all->d.light[--count] = (t_light){a, b};
	}
}
