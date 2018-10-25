/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:48:06 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/25 14:48:23 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_inter	get_intersections(t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	return (s->vtable->get_intersections(a, s, point, dir));
}

t_vec3	get_normal(t_obj *s, t_vec3 point, t_vec3 dir)
{
	return (s->vtable->get_normal(s, point, dir));
}

t_vec3	get_color(t_obj *s)
{
	return (s->vtable->get_color(s));
}
