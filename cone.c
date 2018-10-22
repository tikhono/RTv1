#include "main.h"

static t_inter	get_intersections_cone (t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_cone *cone = (void *)s;
	t_inter	inter;
	t_vec3	oc;
	double	k1;
	double	k2;
	double	k3;
	double	kk;

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

static t_vec3	compute_lightning_cone (t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_cone *closest_cone = (void *)s;
	double		intensity;
	double		length_n;
	double		n_dot_l;
	t_vec3		vec_l;
	t_range		r;
	t_clos		c_int;
	int			i;

	t_vec3 oc = substract(point, closest_cone->center);
	t_vec3 normal = substract(point, closest_cone->center);
	normal = substract(normal, multiply(closest_cone->norm, (1 + pow(tan(closest_cone->angle * M_PI / 360), 2)) * product(dir, closest_cone->norm) * product(oc, closest_cone->norm)));
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
	return (multiply(closest_cone->color, intensity));
}

t_obj	*obj_cone_create(t_vec3 cent, t_vec3 norm, t_vec3 col, double angle)
{
	static t_interface vtable = {
		get_intersections_cone,
		compute_lightning_cone
	};
	static t_obj base = { &vtable };
	t_cone *obj_cone = malloc(sizeof(*obj_cone));
	memcpy(&obj_cone->base, &base, sizeof(base));
	obj_cone->center = cent;
	obj_cone->norm = norm;
	obj_cone->color = col;
	obj_cone->angle = angle;
	return (&obj_cone->base);
}
