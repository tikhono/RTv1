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

static t_vec3	get_normal_sphere(t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_sphere	*closest_sphere = (void *)s;
	t_vec3		normal;

	normal = substract(point, closest_sphere->center);
	normal = normalize(normal);
	return (normal);
}

static t_vec3	get_color_sphere(t_obj *s)
{
	t_sphere	*sphere = (void *)s;
	return (sphere->color);
}

t_obj	*obj_sphere_create(t_vec3 cent, t_vec3 col, double rad)
{
	static t_interface vtable = {
		get_intersections_sphere,
		get_normal_sphere,
		get_color_sphere
	};
	static t_obj base = { &vtable };
	t_sphere *obj_sphere = malloc(sizeof(*obj_sphere));
	memcpy(&obj_sphere->base, &base, sizeof(base));
	obj_sphere->center = cent;
	obj_sphere->color = col;
	obj_sphere->radius = rad;
	return (&obj_sphere->base);
}
