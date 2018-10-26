/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:48:42 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/27 02:23:12 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_inter	get_inter_c(t_all *a, t_obj *s, t_vec3 p, t_vec3 d)
{
	t_cylinder	*c;
	t_inter		inter;
	double		k1;
	double		k2;
	double		k3;

	c = (void *)s;
	p = substract(p, c->center);
	k1 = product(d, d) - product(d, c->norm) * product(d, c->norm);
	k2 = product(p, d) - product(p, c->norm) * product(d, c->norm);
	k3 = product(p, p) - product(p, c->norm) * product(p, c->norm)
		- c->radius * c->radius;
	if (k2 * k2 - k1 * k3 < 0)
	{
		inter.one = INFINITY;
		inter.two = INFINITY;
	}
	else
	{
		inter.one = (-k2 + sqrt(k2 * k2 - k1 * k3)) / k1;
		inter.two = (-k2 - sqrt(k2 * k2 - k1 * k3)) / k1;
	}
	return (inter);
}

static t_vec3	get_normal_c(t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_cylinder	*cylinder;
	t_vec3		oc;
	t_vec3		normal;
	double		prod;

	cylinder = (void *)s;
	oc = substract(point, cylinder->center);
	prod = product(dir, cylinder->norm) * product(oc, cylinder->norm);
	normal = substract(point, cylinder->center);
	normal = substract(normal, multiply(cylinder->norm, prod));
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
