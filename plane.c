/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:48:57 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/26 17:04:39 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_inter	get_inter_p(t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_plane *plane;
	t_inter	inter;

	plane = (void *)s;
	inter.one = product(substract(multiply(plane->norm,
		plane->dist), point), plane->norm) / product(dir, plane->norm);
	inter.two = inter.one;
	return (inter);
}

static t_vec3	get_normal_p(t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_plane	*plane;
	double	dot;

	plane = (void *)s;
	dot = product(plane->norm, dir);
	if (dot < 0)
		return (plane->norm);
	else
		return (multiply(plane->norm, -1));
}

static t_vec3	get_color_p(t_obj *s)
{
	t_plane	*plane;

	plane = (void *)s;
	return (plane->color);
}

t_obj			*obj_plane_create(t_vec3 norm, t_vec3 col, double dist)
{
	t_plane				*obj_plane;
	static t_interface	vtable = {get_inter_p, get_normal_p, get_color_p};
	static t_obj		base = { &vtable };

	obj_plane = malloc(sizeof(*obj_plane));
	memcpy(&obj_plane->base, &base, sizeof(base));
	obj_plane->norm = norm;
	obj_plane->color = col;
	obj_plane->dist = dist;
	return (&obj_plane->base);
}
