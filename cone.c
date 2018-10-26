/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:32 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/26 16:35:52 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_inter	get_inter_c(t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_cone	*cone;
	t_inter	inter;
	t_vec3	oc;
	double	k1;
	double	k2;
	double	k3;
	double	kk;

	cone = (void *)s;
	oc = substract(point, cone->center);
	kk = tan(cone->angle * M_PI / 360);
	kk = 1 + kk * kk;
	k1 = product(dir, dir) - kk * product(dir, cone->norm) * product(dir, cone->norm);
	k2 = 2 * (product(oc, dir) - kk * product(oc, cone->norm) * product(dir, cone->norm));
	k3 = product(oc, oc) - kk * product(oc, cone->norm) * product(oc, cone->norm);
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
	t_cone	*cone;
	t_vec3	normal;
	t_vec3	oc;
	double	prod;

	cone = (void *)s;
	oc = substract(point, cone->center);
	prod = product(dir, cone->norm) * product(oc, cone->norm);
	normal = substract(point, cone->center);
	normal = substract(normal, multiply(cone->norm,
				(1 + pow(tan(cone->angle * M_PI / 360), 2)) * prod));
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
