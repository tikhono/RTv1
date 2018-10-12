#include "main.h"

void	set_direction(t_all *a, int x, int y, t_vec3 *direction)
{
	direction->x = x * a->d.viewport_size / WIDTH;
	direction->y = y * a->d.viewport_size / HEIGHT;
	direction->z = a->d.projection_plane_z;
}

void	get_closest_intersection(t_all *a, double *closest_intersection, t_plane **closest_plane, t_vec3 point, t_vec3 direction, double min, double max)
{
	int 		i;
	double		distant;
	t_inter		inter;

	*closest_intersection = max;
	*closest_plane = NULL;
	i = 0;
	while (i < a->d.obj_arr_length)
	{
	//	(norm * plane_dist - point) ^ norm / direction ^ norm
		a->d.plane_arr[i].norm = multiply(a->d.plane_arr[i].norm, 1 / length(a->d.plane_arr[i].norm));
		distant = product(substract(multiply(a->d.plane_arr[i].norm, a->d.plane_arr[i].dist), point), a->d.plane_arr[i].norm)/ product(direction, a->d.plane_arr[i].norm);
		if (distant < *closest_intersection && distant > min && distant < max)
		{
			*closest_intersection = distant;
			*closest_plane = &a->d.plane_arr[i];
		}
		++i;
	}
}

void	put_pixel(t_all *a, int x, int y, int color)
{
	int len;

	x += WIDTH / 2;
	y += HEIGHT / 2;
	len = y * WIDTH + x;
	a->addr[len] = color;
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
	double		intersection;
	t_plane		*plane;
	t_vec3		vec_l;
	int			i;

	intensity = 0;
	i = 0;
	while (i < a->d.light_arr_length)
	{
		vec_l = substract(a->d.light[i].center, point);
		vec_l = multiply(vec_l, 1 / length(vec_l));
		get_closest_intersection(a, &intersection, &plane, point, vec_l, 0.00001, 1);
		if (plane != NULL || (get_plane_side(closest_plane, a->d.light[i].center) == get_plane_side(closest_plane, a->d.camera_pos)))
		{
			++i;
			continue ;
		}
		intensity += a->d.light[i].intensity;
		++i;
	}
	return (intensity);
}

int		convert_to_int(t_vec3 color)
{
	int	norm_col;

	norm_col = 0;
	color.x = color.x < 0 ? 0 : color.x; 
	norm_col += color.x > 255 ? 255 : color.x;
	norm_col <<= 8;
	color.y = color.y < 0 ? 0 : color.y; 
	norm_col += color.y > 255 ? 255 : color.y;
	norm_col <<= 8;
	color.y = color.z < 0 ? 0 : color.z; 
	norm_col += color.z > 255 ? 255 : color.z;
	return (norm_col);
}


void	trace_ray(t_all *a, int x, int y, t_vec3 direction)
{
	double		closest_intersection;
	double		intensity;
	t_vec3		color;
	t_vec3		point;
	t_plane		*closest_plane;

	get_closest_intersection(a, &closest_intersection, &closest_plane, a->d.camera_pos, direction, 0, INFINITY);
	if (closest_plane == NULL)
		put_pixel(a, x, y, BACKGROUND);
	else if (closest_intersection > 0 && closest_intersection < INFINITY)
	{
		point = add(a->d.camera_pos, multiply(direction, closest_intersection));
		intensity = compute_lighting(a, point, closest_plane);
		color = multiply(closest_plane->color, intensity);
		put_pixel(a, x, y, convert_to_int(color));
	}
}

void	render(t_all *a)
{
	int		x;
	int		y;
	t_vec3	direction;

	x = -WIDTH / 2;
	while (x <= WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while (y <= HEIGHT / 2)
		{
			set_direction(a, x, y, &direction);
			direction = multiply(direction, 1 / length(direction));
			trace_ray(a, x, y, direction);
			++y;
		}
		++x;
	}
	mlx_put_image_to_window(a->p.mlx, a->p.win, a->p.img, 0, 0);
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
	a->d.camera_pos.z = -5;

	a->d.obj_arr_length = 1;
	a->d.plane_arr = (t_plane *)malloc(sizeof(t_plane) * a->d.obj_arr_length);
	a->d.plane_arr[0] = (t_plane){{0, 0.5, 0.1}, {50, 50, 50}, 2};
//	a->d.plane_arr[1] = (t_plane){{-1, 0, 0}, {250, 250, 0}, 0.1};
	a->d.light_arr_length = 1;
	a->d.light = (t_light *)malloc(sizeof(t_light) * a->d.light_arr_length);
	a->d.light[0] = (t_light){{0, -1000, 10}, 1};
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

int		main(int ac, char **av)
{
	t_all	a;

	init(&a);
	render(&a);
	mlx_hook(a.p.win, 2, 5, call_hookers, &a);
	mlx_hook(a.p.win, 17, 1L << 17, exit_mouse, 0);
	mlx_loop(a.p.mlx);
	return (0);
}
