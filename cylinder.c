#include "main.h"

t_inter	get_intersections(t_all *a, t_cylinder *cylinder, t_vec3 point, t_vec3 dir)
{
	t_inter	inter;
	t_vec3	oc;
	double	k1;
	double	k2;
	double	k3;

	oc = substract(point, cylinder->center);
	k1 = product(dir, dir) - product(dir, cylinder->norm) * product(dir, cylinder->norm);
	k2 = 2 * (product(oc, dir) - product(oc, cylinder->norm) * product(dir, cylinder->norm));
	k3 = product(oc, oc) - product(oc, cylinder->norm) * product(oc, cylinder->norm) - cylinder->radius * cylinder->radius;
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

t_closss	get_closest_inter(t_all *a, t_vec3 point, t_vec3 direction, t_range r)
{
	int 		i;
	t_inter		inter;
	t_closss	c_int;

	c_int.dist = r.max;
	c_int.cylinder = NULL;
	i = 0;
	while (i < a->d.obj_arr_length)
	{
		a->d.cyl_arr[i].norm =  multiply(a->d.cyl_arr[i].norm, 1.0 / length(a->d.cyl_arr[i].norm));
		inter = get_intersections(a, &a->d.cyl_arr[i], point, direction);
		if (inter.one < c_int.dist && r.min < inter.one && inter.one < r.max)
		{
			c_int.dist = inter.one;
			c_int.cylinder = &a->d.cyl_arr[i];
		}
		if (inter.two < c_int.dist && r.min < inter.two && inter.two < r.max)
		{
			c_int.dist = inter.two;
			c_int.cylinder = &a->d.cyl_arr[i];
		}
		++i;
	}
	return (c_int);
}

double	compute_lighting(t_all *a, t_vec3 point, t_vec3 direction, t_cylinder *closest_cylinder)
{
	double		intensity;
	double		length_n;
	double		n_dot_l;
	t_vec3		vec_l;
	t_range		r;
	t_closss	c_int;
	int			i;

	t_vec3 oc = substract(point, closest_cylinder->center);
	t_vec3 normal = substract(point, closest_cylinder->center);
	normal = substract(normal, multiply(closest_cylinder->norm, product(direction, closest_cylinder->norm) * product(oc, closest_cylinder->norm)));
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
		if (c_int.cylinder != NULL)
		{
			++i;
			continue ;
		}
		n_dot_l = product(normal, vec_l);
		if (n_dot_l > 0)
			intensity += a->d.light[i].intensity * n_dot_l / (length_n * length(vec_l));
		++i;
	}
	return (intensity);
}

void	trace_ray(t_all *a, int x, int y, t_vec3 direction)
{
	t_closss	clos_inter;
	double		intensity;
	t_range		range;
	t_vec3		color;
	t_vec3		point;

	range.min = 0;
	range.max = INFINITY;
	clos_inter = get_closest_inter(a, a->d.camera_pos, direction, range);
	if (clos_inter.cylinder == NULL)
		put_pixel(a, x, y, BACKGROUND);
	else if (clos_inter.dist > 0 && clos_inter.dist < INFINITY)
	{
		point = add(a->d.camera_pos, multiply(direction, clos_inter.dist));
		intensity = compute_lighting(a, point, direction, clos_inter.cylinder);
		color = multiply(clos_inter.cylinder->color, intensity);
		put_pixel(a, x, y, convert_to_int(color));
	}
}

void	init(t_all *a)
{
	a->p.mlx = mlx_init();
	a->p.img = mlx_new_image(a->p.mlx, WIDTH, HEIGHT);
	a->p.win = mlx_new_window(a->p.mlx, WIDTH, HEIGHT, "start");
	a->addr = (int *)mlx_get_data_addr(a->p.img, &a->p.x, &a->p.y, &a->p.z);
	a->d.viewport_size = 1.0;
	a->d.projection_plane_z = 1.0;
	a->d.camera_pos.x = 0;
	a->d.camera_pos.y = 0;
	a->d.camera_pos.z = 0;

	a->d.obj_arr_length = 1;
	a->d.cyl_arr = (t_cylinder *)malloc(sizeof(t_cylinder) * a->d.obj_arr_length);
	a->d.cyl_arr[0] = (t_cylinder){{0, 0, 10}, {1, 1, 0}, {255, 0, 0}, 1};
	a->d.light_arr_length = 1;
	a->d.light = (t_light *)malloc(sizeof(t_light) * a->d.light_arr_length);
	a->d.light[0] = (t_light){{0, 0, 0}, 1};
}
