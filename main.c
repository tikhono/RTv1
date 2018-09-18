#include "main.h"

void	set_direction(t_all *a, int x, int y)
{
	a->d->direction.x = x * a->d->viewport_size / a->d->width;
	a->d->direction.y = y * a->d->viewport_size / a->d->height;
	a->d->direction.z = a->d->projection_plane_z; 
}

void	get_intersections(t_all *a, t_sphere *sphere, double *intersection1, double *intersection2)
{
	t_vec3	oc = substract(a->d->camera_pos, sphere->center);
	double	k1 = product(a->d->direction, a->d->direction);
	double	k2 = 2 * product(oc, a->d->direction);
	double	k3 = product(oc, oc) - sphere->radius * sphere->radius;
	double	discriminant = k2*k2 - 4*k1*k3;
	if (discriminant >= 0)
	{
		*intersection1 = (-k2 + sqrt(discriminant)) / 2*k1;
		*intersection2 = (-k2 - sqrt(discriminant)) / 2*k1;
	}
}

void	put_pixel(t_all *a, int x, int y, int color)
{
	a->p->addr[x * a->d->width + y] = color;
}

void	trace_ray(t_all *a, int x, int y, int i)
{
	double		min;
	double		max;
	double		intersection1;
	double		intersection2;
	double		closest_intersection;
	t_sphere	*closest_sphere;

	min = 1.0;
	max = INFINITY;
	closest_intersection = INFINITY;
	closest_sphere = NULL;
	i = 0;
	while (i < a->d->arr_lenth)
	{
		get_intersections(a, &a->d->arr[i], &intersection1, &intersection2);
		if (intersection1 < closest_intersection && min < intersection1 && intersection1 < max)
		{
			closest_intersection = intersection1;
			closest_sphere = &a->d->arr[i];
		}
		if (intersection2 < closest_intersection && min < intersection2 && intersection2 < max)
		{
			closest_intersection = intersection2;
			closest_sphere = &a->d->arr[i];
		}
	}
	if (closest_sphere == NULL)
		put_pixel(a, x, y, a->d->background_color);
	put_pixel(a, x, y, a->d->arr[i].color);
}

void	render(t_all *a)
{
	int	x;
	int	y;
	int	i;

	x = -a->d->width / 2;
	while (x < a->d->width / 2)
	{
		y = -a->d->height / 2;
		while (y < a->d->height / 2)
		{
			set_direction(a, x, y);
			trace_ray(a, x, y, i);
			++y;
		}
		++x;
	}
	mlx_put_image_to_window(a->p->mlx, a->p->win, a->p->img, 0, 0);
}

void	init(t_all *a)
{
	t_mlx	*p;
	t_data	*d;
	int		x;
	int		y;
	int		z;
	
	a->p = p;
	a->d = d;
	a->d->width = 1024;
	a->d->height = 512;
	a->d->viewport_size = 1.0;
	a->d->projection_plane_z = 1.0;
	a->d->background_color = 0xffffff;
	a->d->camera_pos.x = 0;
	a->d->camera_pos.y = 0;
	a->d->camera_pos.z = 0;
	a->d->arr_lenth = 3;
	a->d->arr = (t_sphere *)malloc(sizeof(t_sphere *) * a->d->arr_lenth);
	a->d->arr[0] = (t_sphere){{1, 1, 1}, 2, 0xFF0000};
	a->d->arr[1] = (t_sphere){{0, 0, 1}, 1, 0x00FF00};
	a->d->arr[2] = (t_sphere){{1, 0, 0}, 2, 0x0000FF};
	printf("OK\n");
	a->p->mlx = mlx_init();
	printf("OK\n");
	a->p->win = mlx_new_window(a->p->mlx, a->d->width, a->d->height, "start");
	a->p->img = mlx_new_image(a->p->mlx, a->d->width, a->d->height);
	a->addr = (int *)mlx_get_data_addr(a->p->img, &x, &y, &z);
}

int		main(int ac, char **av)
{
	t_all	a;

	init(&a);
	render(&a);
	mlx_hook(a.p->win, 2, 5, call_hookers, &a);
	mlx_hook(a.p->win, 17, 1L << 17, exit_mouse, 0);
	mlx_loop(a.p->mlx);
	return (0);
}
