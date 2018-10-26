/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 11:27:07 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/26 16:00:45 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		call_hookers(int key, t_all *a)
{
	if (key == 53)
		exit(0);
	return (0);
}

int		exit_mouse(void)
{
	exit(0);
	return (0);
}

t_vec3	rotate(t_vec3 vec, t_vec3 rot)
{
	double	tempo;

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
