#include "main.h"

static t_inter	get_intersections_plane (t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_plane *plane = (void *)s;
	t_inter	inter;

	inter.one = product(substract(multiply(plane->norm,
		plane->dist), point) , plane->norm) / product(dir, plane->norm);
	inter.two = inter.one;	
	return (inter);
}

int		get_plane_side(t_plane *plane, t_vec3 point)
{
	t_vec3	n;
	t_vec3	point_p;
	double	res;

	n = multiply(plane->norm, 1 / length(plane->norm));
	point_p = multiply(n, plane->dist);
	res = product(n, substract(point_p, point));
	if (res == 0)
		return (0);
	return (res > 0 ? 1 : -1);
}
/*
static t_vec3	compute_lightning_plane (t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_plane *closest_plane = (void *)s;
	double		intensity;
	double		length_n;
	double		n_dot_l;
	t_vec3		vec_l;
	t_range		r;
	t_clos		c_int;
	int			i;

	r.min = 0.0001;
	r.max = 1;
	intensity = 0;
	i = 0;
	while (i < a->d.light_arr_length)
	{
		vec_l = substract(a->d.light[i].center, point);
		c_int = get_closest_inter(a, point, vec_l, r);
		if (c_int.obj != NULL || (get_plane_side(closest_plane, a->d.light[i].center) != get_plane_side(closest_plane, a->d.camera_pos)))
		{
			++i;
			continue ;
		}
		n_dot_l = product(closest_plane->norm, vec_l);
		if (n_dot_l > 0)
			intensity += a->d.light[i].intensity * n_dot_l /  length(vec_l);
		++i;
	}
	return (multiply(closest_plane->color, intensity));
}
*/

static t_vec3	get_normal_plane(t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_plane	*plane = (void *)s;
	
	return (plane->norm);
}
static t_vec3	get_color_plane(t_obj *s)
{
	t_plane	*plane = (void *)s;
	return (plane->color);
}

t_obj	*obj_plane_create(t_vec3 norm, t_vec3 col, double dist)
{
	static t_interface vtable = {
		get_intersections_plane,
		get_normal_plane,
		get_color_plane
	};
	static t_obj base = { &vtable };
	t_plane *obj_plane = malloc(sizeof(*obj_plane));
	memcpy(&obj_plane->base, &base, sizeof(base));
	obj_plane->norm = norm;
	obj_plane->color = col;
	obj_plane->dist = dist;
	return (&obj_plane->base);
}
