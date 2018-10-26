/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:48:42 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/26 16:43:12 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_inter	get_inter_c(t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_cylinder *obj_cyli = (void *)s;
	t_inter	inter;
	t_vec3	oc;
	double	k1;
	double	k2;
	double	k3;

	oc = substract(point, obj_cyli->center);
	k1 = product(dir, dir) - product(dir, obj_cyli->norm) * product(dir, obj_cyli->norm);
	k2 = 2 * (product(oc, dir) - product(oc, obj_cyli->norm) * product(dir, obj_cyli->norm));
	k3 = product(oc, oc) - product(oc, obj_cyli->norm) * product(oc, obj_cyli->norm) - obj_cyli->radius * obj_cyli->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
	{
		inter.one = INFINITY;
		inter.two = INFINITY;
	}
	else
	{
		inter.one = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / 2 * k1;
		inter.two = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / 2 * k1;
	}
	return (inter);
}

static t_vec3	get_normal_c(t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_cylinder	*clos_cylinder;
	t_vec3		oc;
	t_vec3		normal;
	double		prod;

	clos_cylinder = (void *)s;
	oc = substract(point, clos_cylinder->center);
	prod = product(dir, clos_cylinder->norm) * product(oc, clos_cylinder->norm);
	normal = substract(point, clos_cylinder->center);
	normal = substract(normal, multiply(clos_cylinder->norm, prod));
	normal = normalize(normal);
	return (normal);
}

static t_vec3	get_color_c(t_obj *s)
{
	t_cylinder	*cyli;

	cyli = (void *)s;
	return (cyli->color);
}

t_obj			*obj_cyli_create(t_vec3 cent,
		t_vec3 norm, t_vec3 col, double rad)
{
	t_cylinder			*obj_cyli;
	static t_interface	vtable = {get_inter_c, get_normal_c, get_color_c};
	static t_obj		base = { &vtable };

	obj_cyli = malloc(sizeof(*obj_cyli));
	memcpy(&obj_cyli->base, &base, sizeof(base));
	obj_cyli->center = cent;
	obj_cyli->norm = norm;
	obj_cyli->color = col;
	obj_cyli->radius = rad;
	return (&obj_cyli->base);
}
