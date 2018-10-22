#include "main.h"

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
		color = compute_lightning(a, clos_inter.obj, point, dir);
		put_pixel(a, x, y, convert_to_int(color));
	}
}
