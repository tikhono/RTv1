#include "main.h"

t_vec3	normalize(t_vec3 a)
{
	return (multiply(a, 1 / length(a)));
}

double	compute_intensity(t_obj *s, t_vec3 normal, t_vec3 vec_l, double	l_int)
{
	double	intensity;
	double	n_dot_l;

	intensity = 0;
	n_dot_l = product(normal, vec_l);
	if (n_dot_l > 0)
		intensity += l_int * n_dot_l / length(vec_l);
	// Specular reflection.
	/*
	if (specular != -1) {
	var vec_r = Subtract(Multiply(2.0*DotProduct(normal, vec_l), normal), vec_l);
	var r_dot_v = DotProduct(vec_r, view);
	if (r_dot_v > 0) {
		intensity += light.intensity * Math.pow(r_dot_v / (Length(vec_r) * length_v), specular); 
	}
*/
	return (intensity);
}

t_vec3	compute_color(t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	t_vec3		vec_l;
	t_range		r;
	t_clos		c_int;
	int			i;
	double		intensity;

	r.min = 0.0001;
	r.max = 1;
	i = 0;
	while (i < a->d.light_arr_length)
	{
		vec_l = normalize(substract(a->d.light[i].center, point));
		c_int = get_closest_inter(a, point, vec_l, r);
		if (c_int.obj != NULL)
		{
			++i;
			continue ;
		}
		intensity += compute_intensity(c_int.obj, get_normal(s, point, dir), vec_l, a->d.light[i].intensity);
		++i;
	}
	return (multiply(get_color(s), intensity));
}

t_clos	get_closest_inter(t_all *a, t_vec3 point, t_vec3 direction, t_range r)
{
	int 		i;
	t_inter		inter;
	t_clos		c_int;

	c_int.dist = r.max;
	c_int.obj = NULL;
	i = 0;
	while (i < a->d.obj_arr_length)
	{
		inter = get_intersections(a, a->d.obj_arr[i], point, direction);
		if (inter.one < c_int.dist && r.min < inter.one && inter.one < r.max)
		{
			c_int.dist = inter.one;
			c_int.obj = a->d.obj_arr[i];
		}
		if (inter.two < c_int.dist && r.min < inter.two && inter.two < r.max)
		{
			c_int.dist = inter.two;
			c_int.obj = a->d.obj_arr[i];
		}
		++i;
	}
	return (c_int);
}

void	trace_ray(t_all *a, int x, int y, t_vec3 dir)
{
	t_clos		clos_inter;
	t_range		range;
	t_vec3		point;
	t_vec3		color;

	range.min = 0;
	range.max = INFINITY;
	clos_inter = get_closest_inter(a, a->d.camera_pos, dir, range);
	if (clos_inter.obj == NULL)
		put_pixel(a, x, y, BACKGROUND);
	else if (clos_inter.dist > 0 && clos_inter.dist < INFINITY)
	{
		point = add(a->d.camera_pos, multiply(dir, clos_inter.dist));
		color = compute_color(a, clos_inter.obj, point, dir);
		put_pixel(a, x, y, convert_to_int(color));
	}
}