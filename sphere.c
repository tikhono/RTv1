#include "main.h"

static t_inter	get_intersections_sphere (t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_sphere *sphere = (void *)s;
	t_inter	inter;
	t_vec3	oc;
	double	k1;
	double	k2;
	double	k3;

	oc = substract(point, sphere->center);
	k1 = 2 * product(dir, dir);
	k2 = 2 * product(oc, dir);
	k3 = product(oc, oc) - sphere->radius * sphere->radius;
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

static t_vec3	compute_lightning_sphere (t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_sphere *closest_sphere = (void *)s;
	double		intensity;
	double		length_n;
	double		n_dot_l;
	t_vec3		vec_l;
	t_range		r;
	t_clos		c_int;
	int			i;

	t_vec3 normal = substract(point, closest_sphere->center);
	normal = multiply(normal, 1.0 / length(normal));
	intensity = 0;
	length_n = length(normal);
	r.min = 0.0001;
	r.max = 1;
	i = 0;
	while (i < a->d.light_arr_length)
	{
		vec_l = substract(a->d.light[i].center, point);
		vec_l = multiply(vec_l, 1 / length(vec_l));
		c_int = get_closest_inter(a, point, vec_l, r);
		if (c_int.obj != NULL)
		{
			++i;
			continue ;
		}
		n_dot_l = product(normal, vec_l);
		if (n_dot_l > 0)
			intensity += a->d.light[i].intensity * n_dot_l / (length_n * length(vec_l));
		++i;
	}
	return (multiply(closest_sphere->color, intensity));
}

t_obj	*obj_sphere_create(t_vec3 cent, t_vec3 col, double rad)
{
	static t_interface vtable = {
		get_intersections_sphere,
		compute_lightning_sphere
	};
	static t_obj base = { &vtable };
	t_sphere *obj_sphere = malloc(sizeof(*obj_sphere));
	memcpy(&obj_sphere->base, &base, sizeof(base));
	obj_sphere->center = cent;
	obj_sphere->color = col;
	obj_sphere->radius = rad;
	return (&obj_sphere->base);
}
