#include "main.h"

void	set_direction(t_all *a, int x, int y, t_vec3 *direction)
{
	direction->x = x * a->d.viewport_size / WIDTH;
	direction->y = y * a->d.viewport_size / HEIGHT;
	direction->z = a->d.projection_plane_z;
}

void	get_intersections(t_all *a, t_sphere *sphere, t_inter *inter, t_vec3 point, t_vec3 direction)
{
	t_vec3	oc = substract(point, sphere->center);
	double	k1 = product(direction, direction);
	double	k2 = 2 * product(oc, direction);
	double	k3 = product(oc, oc) - sphere->radius * sphere->radius;
	double	discriminant = k2*k2 - 4*k1*k3;

	if (discriminant < 0)
	{
		inter->one = INFINITY;
		inter->two = INFINITY;
	}
	else
	{
		inter->one = (-k2 + sqrt(discriminant)) / 2*k1;
		inter->two = (-k2 - sqrt(discriminant)) / 2*k1;
	}
}

void	get_closest_intersection(t_all *a, double *closest_intersection, t_sphere **closest_sphere, t_vec3 point, t_vec3 direction, double min, double max)
{
	int 		i;
	t_inter		inter;

	*closest_intersection = max;
	*closest_sphere = NULL;
	i = 0;
	while (i < a->d.obj_arr_length)
	{
		get_intersections(a, &a->d.arr[i], &inter, point, direction);
		if (inter.one < *closest_intersection && min < inter.one && inter.one < max)
		{
			*closest_intersection = inter.one;
			*closest_sphere = &a->d.arr[i];
		}
		if (inter.two < *closest_intersection && min < inter.two && inter.two < max)
		{
			*closest_intersection = inter.two;
			*closest_sphere = &a->d.arr[i];
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


double	compute_lighting(t_all *a, t_vec3 point, t_vec3 normal)
{
	double		intensity;
	double		length_n;
	double		n_dot_l;
	double		intersection;
	t_sphere	*sphere;
	t_vec3		vec_l;
	int			i;

	intensity = 0;
	length_n = length(normal);
	i = 0;
	while (i < a->d.light_arr_length)
	{
		vec_l = substract(a->d.light[i].center, point);
		vec_l = multiply(vec_l, 1 / length(vec_l));
		get_closest_intersection(a, &intersection, &sphere, point, vec_l, 0.001, 1);
		if (sphere != NULL)
		{
			printf("Shadow! Intersection: %f\n", intersection);
			i++;
			continue ;
		}
		n_dot_l = product(normal, vec_l);
		if (n_dot_l > 0)
			intensity += a->d.light[i].intensity * n_dot_l / (length_n * length(vec_l));
		i++;
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
	t_sphere	*closest_sphere;

	get_closest_intersection(a, &closest_intersection, &closest_sphere, a->d.camera_pos, direction, 0, INFINITY);
	if (closest_sphere == NULL)
		put_pixel(a, x, y, BACKGROUND);
	else if (closest_intersection > 0 && closest_intersection < INFINITY)
	{
		t_vec3 point = add(a->d.camera_pos, multiply(direction, closest_intersection));
		t_vec3 normal = substract(point, closest_sphere->center);
		normal = multiply(normal, 1.0 / length(normal));
		intensity = compute_lighting(a, point, normal);
		color = multiply(closest_sphere->color, intensity);
	//	printf("%f, %f, %f\n", point.x, point.y, point.z);
/*
		printf("%d %d\n", x, y);
		printf("%f\t%f\t%f\n", closest_sphere->color.x, closest_sphere->color.y, closest_sphere->color.z);
		printf("intensity %f\n", intensity);
		printf("%f\t%f\t%f\n", color.x, color.y, color.z);
*/
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
	a->d.camera_pos.z = -2;

	a->d.obj_arr_length = 2;
	a->d.arr = (t_sphere *)malloc(sizeof(t_sphere) * a->d.obj_arr_length);
	a->d.arr[0] = (t_sphere){{0, 0, 3}, {255, 5, 5}, 0.3};
	a->d.arr[1] = (t_sphere){{0, 5000.5, 3}, {255, 255, 0}, 5000};
	a->d.light_arr_length = 1;
	a->d.light = (t_light *)malloc(sizeof(t_light) * a->d.light_arr_length);
	a->d.light[0] = (t_light){{0, -10, 10}, 1};
/*
	a->d.obj_arr_length = 2;
	a->d.arr = (t_sphere *)malloc(sizeof(t_sphere) * a->d.obj_arr_length);
	a->d.arr[0] = (t_sphere){{-0.75, 0, 3}, {255, 5, 5}, 0.2};
	a->d.arr[1] = (t_sphere){{0, 0, 3}, {255, 255, 0}, 0.2};
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
