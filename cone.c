/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:32 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/27 02:49:26 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_inter	get_inter_c(t_all *a, t_obj *s, t_vec3 p, t_vec3 d)
{
	t_cone	*c;
	t_inter	inter;
	double	k1;
	double	k2;
	double	k3;

	c = (void *)s;
	p = substract(p, c->center);
	k1 = product(d, d) - c->angle * product(d, c->norm) * product(d, c->norm);
	k2 = product(p, d) - c->angle * product(p, c->norm) * product(d, c->norm);
	k3 = product(p, p) - c->angle * product(p, c->norm) * product(p, c->norm);
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
	t_cone	*cone;
	t_vec3	oc;
	t_vec3	normal;
	double	prod;

	cone = (void *)s;
	oc = substract(point, cone->center);
	prod = product(dir, cone->norm) * product(oc, cone->norm);
	normal = substract(point, cone->center);
	normal = substract(normal, multiply(cone->norm, prod * cone->angle));
	normal = normalize(normal);
	return (normal);
}

static t_vec3	get_color_c(t_obj *s)
{
	t_cone	*cone;

	cone = (void *)s;
	return (cone->color);
}

t_obj			*obj_cone_create(t_vec3 cent, t_vec3 norm, t_vec3 col, double a)
{
	t_cone				*obj_cone;
	static t_interface	vtable = {get_inter_c, get_normal_c, get_color_c};
	static t_obj		base = { &vtable };

	obj_cone = malloc(sizeof(*obj_cone));
	memcpy(&obj_cone->base, &base, sizeof(base));
	obj_cone->center = cent;
	obj_cone->norm = norm;
	obj_cone->color = col;
	obj_cone->angle = a;
	return (&obj_cone->base);
}
