#include "main.h"

t_clos	get_closest_inter(t_all *a, t_vec3 point, t_vec3 direction, t_range r)
{
	t_clos	c_int;
	double	dist;
	int		i;

	c_int.dist = r.max;
	c_int.plane = NULL;
	i = 0;
	while (i < a->d.obj_arr_length)
	{
		a->d.plane_arr[i].norm = multiply(a->d.plane_arr[i].norm,
			1 / length(a->d.plane_arr[i].norm));
		dist = product(substract(multiply(a->d.plane_arr[i].norm,
			a->d.plane_arr[i].dist), point) , a->d.plane_arr[i].norm) /
			product(direction, a->d.plane_arr[i].norm);
		if (dist < c_int.dist && dist > r.min && dist < r.max)
		{
			c_int.dist = dist;
			c_int.plane = &a->d.plane_arr[i];
		}
		++i;
	}
	return (c_int);
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

double	compute_lighting(t_all *a, t_vec3 point, t_plane *closest_plane)
{
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
		if (c_int.plane != NULL || (get_plane_side(closest_plane, a->d.light[i].center) != get_plane_side(closest_plane, a->d.camera_pos)))
		{
			++i;
			continue ;
		}
		intensity += a->d.light[i].intensity;
		++i;
	}
	return (intensity);
}

void	trace_ray(t_all *a, int x, int y, t_vec3 direction)
{
	t_clos		clos_inter;
	double		intensity;
	t_range		range;
	t_vec3		color;
	t_vec3		point;

	range.min = 0;
	range.max = INFINITY;
	clos_inter = get_closest_inter(a, a->d.camera_pos, direction, range);
	if (clos_inter.plane == NULL)
		put_pixel(a, x, y, BACKGROUND);
	else if (clos_inter.dist > 0 && clos_inter.dist < INFINITY)
	{
		point = add(a->d.camera_pos, multiply(direction, clos_inter.dist));
		intensity = compute_lighting(a, point, clos_inter.plane);
		color = multiply(clos_inter.plane->color, intensity);
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
	a->d.camera_pos.z = -1;

	a->d.obj_arr_length = 2;
	a->d.plane_arr = (t_plane *)malloc(sizeof(t_plane) * a->d.obj_arr_length);
	a->d.plane_arr[0] = (t_plane){{0, 0.5, 0}, {50, 50, 50}, 2};
	a->d.plane_arr[1] = (t_plane){{1, 0, 0.1}, {250, 250, 0}, 0};
	a->d.light_arr_length = 1;
	a->d.light = (t_light *)malloc(sizeof(t_light) * a->d.light_arr_length);
	a->d.light[0] = (t_light){{-10, -2, 0}, 1};
/*
	a->d.obj_arr_length = 2;
	a->d.arr = (t_plane *)malloc(sizeof(t_plane) * a->d.obj_arr_length);
	a->d.arr[0] = (t_plane){{-0.75, 0, 3}, {255, 5, 5}, 0.2};
	a->d.arr[1] = (t_plane){{0, 0, 3}, {255, 255, 0}, 0.2};
	a->d.light_arr_length = 1;
	a->d.light = (t_light *)malloc(sizeof(t_light) * a->d.light_arr_length);
	a->d.light[0] = (t_light){{10, 0, 3}, 1};
*/
}
