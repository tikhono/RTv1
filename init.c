#include "main.h"

void	set_params(t_vec3 *a, t_vec3 *b, t_vec3 *c, double *d)
{
	a->x = 0;
	a->y = 0;
	a->z = 1;
	b->x = 0;
	b->y = -1;
	b->z = 0;
	*b =  normalize(*b);
	c->x = 255;
	c->y = 0;
	c->z = 0;
	*d = -2;
}

void	init(t_all *a)
{
	t_vec3	a1;//made it one structure
	t_vec3	b1;
	t_vec3	c1;
	double	d1;

	set_params(&a1, &b1, &c1, &d1);
	a->p.mlx = mlx_init();
	a->p.img = mlx_new_image(a->p.mlx, WIDTH, HEIGHT);
	a->p.win = mlx_new_window(a->p.mlx, WIDTH, HEIGHT, "start");
	a->addr = (int *)mlx_get_data_addr(a->p.img, &a->p.x, &a->p.y, &a->p.z);
	a->d.viewport_size = 1.0;
	a->d.projection_plane_z = 1.0;
	a->d.camera_pos.x = 0;
	a->d.camera_pos.y = 0;
	a->d.camera_pos.z = 0;

	a->d.obj_arr_length = 2;
	a->d.obj_arr = (t_obj **)malloc(sizeof(t_obj *) * a->d.obj_arr_length);
	a->d.obj_arr[0] = obj_plane_create(b1, c1, d1);
	b1.x = 1;
	b1.y = 0;
	a->d.obj_arr[1] = obj_plane_create(b1, c1, d1);
	a->d.light_arr_length = 1;
	a->d.light = (t_light *)malloc(sizeof(t_light) * a->d.light_arr_length);
	a->d.light[0] = (t_light){{-3, 0, 0}, 1};
}
