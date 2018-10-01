#include "main.h"

void	set_direction(t_all *a, int x, int y)
{
	a->d.direction.x = x * a->d.viewport_size / WIDTH;
	a->d.direction.y = y * a->d.viewport_size / HEIGHT;
	a->d.direction.z = a->d.projection_plane_z;
}

void	get_intersections(t_all *a, t_sphere *sphere, double *intersection1, double *intersection2)
{
	t_vec3	oc = substract(a->d.camera_pos, sphere->center);
	double	k1 = product(a->d.direction, a->d.direction);
	double	k2 = 2 * product(oc, a->d.direction);
	double	k3 = product(oc, oc) - sphere->radius * sphere->radius;
	double	discriminant = k2*k2 - 4*k1*k3;
	if (discriminant >= 0)
	{
		*intersection1 = (-k2 + sqrt(discriminant)) / 2*k1;
		*intersection2 = (-k2 - sqrt(discriminant)) / 2*k1;
	}
	else
	{
		*intersection1 = INFINITY;
		*intersection2 = INFINITY;
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


double	compute_lighting(t_all *a, t_vec3 point, t_vec3 normal)
{
	double	intensity;
	double	length_n;
	double	n_dot_l;
	t_vec3	vec_l;
	int		i;

	intensity = 0;
	length_n = length(normal);
	i = 0;
	while (i < a->d.light_arr_length)
	{
		vec_l = substract(a->d.light[i].center, point);
		// Shadow check.
		//var blocker = ClosestIntersection(point, vec_l, EPSILON, t_max);
		//if (blocker)
		//	continue;
		n_dot_l = product(normal, vec_l);
		if (n_dot_l > 0)
			intensity += a->d.light[i].intensity * n_dot_l / (length_n * length(vec_l));
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

void	get_closest_intersection(t_all *a, double *closest_intersection, t_sphere **closest_sphere)
{
	int 		i;
	double		min;
	double		max;
	double		intersection1;
	double		intersection2;

	min = 1.0;
	max = INFINITY;
	*closest_intersection = INFINITY;
	*closest_sphere = NULL;
	i = 0;
	while (i < a->d.obj_arr_length)
	{
		get_intersections(a, &a->d.arr[i], &intersection1, &intersection2);
		if (intersection1 < *closest_intersection && min < intersection1 && intersection1 < max)
		{
			*closest_intersection = intersection1;
			*closest_sphere = &a->d.arr[i];
		}
		if (intersection2 < *closest_intersection && min < intersection2 && intersection2 < max)
		{
			*closest_intersection = intersection2;
			*closest_sphere = &a->d.arr[i];
		}
		++i;
	}
	printf("%p\t", closest_sphere);
}

void	trace_ray(t_all *a, int x, int y)
{
	double		closest_intersection;
	t_vec3		color;
	t_sphere	*closest_sphere;

	get_closest_intersection(a, &closest_intersection, &closest_sphere);
	printf("%p\n", closest_sphere);
	if (closest_sphere == NULL)
		put_pixel(a, x, y, BACKGROUND);
	else
	{
		t_vec3 point = add(a->d.camera_pos, multiply(a->d.direction, closest_intersection));
		t_vec3 normal = substract(point, closest_sphere->center);
		normal = multiply(normal, 1.0 / length(normal));
		color = multiply(closest_sphere->color, compute_lighting(a, point, normal));
		put_pixel(a, x, y, convert_to_int(color));
	}
}

void	render(t_all *a)
{
	int	x;
	int	y;

	x = -WIDTH / 2;
	while (x <= WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while (y <= HEIGHT / 2)
		{
			set_direction(a, x, y);
			trace_ray(a, x, y);
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
	a->d.camera_pos.z = 0;
	a->d.obj_arr_length = 4;
	a->d.arr = (t_sphere *)malloc(sizeof(t_sphere) * a->d.obj_arr_length);
	a->d.arr[0] = (t_sphere){{0, -1, 3}, {255, 5, 5}, 1};
	a->d.arr[1] = (t_sphere){{2, 0, 4}, {0, 0, 255}, 1};
	a->d.arr[2] = (t_sphere){{-2, 0, 4}, {0, 255, 0},1};
	a->d.arr[3] = (t_sphere){{0, 5001, 0}, {255, 255, 0}, 5000};
	a->d.light_arr_length = 4;
	a->d.light = (t_light *)malloc(sizeof(t_light) * a->d.light_arr_length);
	a->d.light[0] = (t_light){{0.0, -1.0, 3.0}, 1.0};
	a->d.light[1] = (t_light){{0.0, 0.0, 0.0}, 1.0};
	a->d.light[2] = (t_light){{-2.0, 0.0, 4.0}, 1.0};
	a->d.light[3] = (t_light){{0, 0, 0}, 50};
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
