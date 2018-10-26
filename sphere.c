/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:32:36 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/26 23:54:31 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_inter	get_inter_s(t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_sphere	*sphere;
	t_inter		inter;
	double		k1;
	double		k2;
	double		k3;

	sphere = (void *)s;
	point = substract(point, sphere->center);
	k1 = 2 * product(dir, dir);
	k2 = 2 * product(point, dir);
	k3 = product(point, point) - sphere->radius * sphere->radius;
	if (k2 * k2 - 2 * k1 * k3 < 0)
	{
		inter.one = INFINITY;
		inter.two = INFINITY;
	}
	else
	{
		inter.one = (-k2 + sqrt(k2 * k2 - 2 * k1 * k3)) / k1;
		inter.two = (-k2 - sqrt(k2 * k2 - 2 * k1 * k3)) / k1;
	}
	return (inter);
}

static t_vec3	get_normal_s(t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_sphere	*closest_sphere;
	t_vec3		normal;

	closest_sphere = (void *)s;
	normal = substract(point, closest_sphere->center);
	normal = normalize(normal);
	return (normal);
}

static t_vec3	get_color_s(t_obj *s)
{
	t_sphere	*sphere;

	sphere = (void *)s;
	return (sphere->color);
}

t_obj			*obj_sphere_create(t_vec3 cent, t_vec3 col, double rad)
{
	t_sphere			*obj_sphere;
	static t_interface	vtable = {get_inter_s, get_normal_s, get_color_s};
	static t_obj		base = { &vtable };

	obj_sphere = malloc(sizeof(*obj_sphere));
	memcpy(&obj_sphere->base, &base, sizeof(base));
	obj_sphere->center = cent;
	obj_sphere->color = col;
	obj_sphere->radius = rad;
	return (&obj_sphere->base);
}
