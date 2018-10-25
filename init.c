#include "main.h"

void	push_list(t_node **head, t_obj *obj)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->obj = obj;
	new_node->next = *head;
	*head = new_node;
}

void	init(t_all *a, char *file)
{
	a->p.mlx = mlx_init();
	a->p.img = mlx_new_image(a->p.mlx, WIDTH, HEIGHT);
	a->p.win = mlx_new_window(a->p.mlx, WIDTH, HEIGHT, "start");
	a->addr = (int *)mlx_get_data_addr(a->p.img, &a->p.x, &a->p.y, &a->p.z);
	a->d.viewport_size = 1.0;
	a->d.projection_plane_z = 1.0;
	a->d.file = file;
	a->d.obj_list = NULL;
	parse(a);
}
