#include "main.h"

void	set_direction(t_all *a, int x, int y, t_vec3 *direction)
{
	direction->x = x * a->d.viewport_size / WIDTH;
	direction->y = y * a->d.viewport_size / HEIGHT;
	direction->z = a->d.projection_plane_z;
}

void	put_pixel(t_all *a, int x, int y, int color)
{
	int len;

	x += WIDTH / 2;
	y += HEIGHT / 2;
	len = y * WIDTH + x;
	a->addr[len] = color;
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
