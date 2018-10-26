/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:29:48 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/25 17:18:12 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	norm_col += color.x > 255 ? 255 : (int)color.x;
	norm_col <<= 8;
	color.y = color.y < 0 ? 0 : color.y;
	norm_col += color.y > 255 ? 255 : (int)color.y;
	norm_col <<= 8;
	color.z = color.z < 0 ? 0 : color.z;
	norm_col += color.z > 255 ? 255 : (int)color.z;
	return (norm_col);
}

t_vec3	get_dir(t_all *a, int x, int y)
{
	t_vec3	dir;

	dir.x = x * a->d.viewport_size / WIDTH;
	dir.y = y * a->d.viewport_size / HEIGHT;
	dir.z = a->d.projection_plane_z;
	dir = rotate(dir, a->d.camera_rot);
	return (dir);
}

void	render(t_all *a)
{
	int		x;
	int		y;
	t_vec3	dir;

	x = -WIDTH / 2;
	while (x <= WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while (y <= HEIGHT / 2)
		{
			dir = get_dir(a, x, y);
			trace_ray(a, x, y, dir);
			++y;
		}
		++x;
	}
	mlx_put_image_to_window(a->p.mlx, a->p.win, a->p.img, 0, 0);
}

int		main(int ac, char **av)
{
	t_all	a;

	init(&a, av[1]);
	render(&a);
	mlx_hook(a.p.win, 2, 5, call_hookers, &a);
	mlx_hook(a.p.win, 17, 1L << 17, exit_mouse, 0);
	mlx_loop(a.p.mlx);
	return (0);
}
