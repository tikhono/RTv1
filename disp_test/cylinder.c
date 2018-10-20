#include "test.h"

static int	get_closest_inter_cyli (t_obj *s)
{
	t_cylinder *cyli = (void *)s;
	printf("cyli intersect was computed %f\n");
}

static int	compute_lightning_cyli (t_obj *s)
{
	printf("cyli lightning was computed\n");
}

t_obj *obj_cyli_create (t_vec3 cent, t_vec3 norm, t_vec3 col, double rad)
{
	static const t_interface vtable = {
		get_closest_inter_cyli,
		compute_lightning_cyli
	};
	static t_obj base = { &vtable };
	t_cylinder *obj_cyli = malloc(sizeof(*obj_cyli));
	memcpy(&obj_cyli->base, &base, sizeof(base));
	obj_cyli->center = cent;
	obj_cyli->norm = norm;
	obj_cyli->color = col;
	obj_cyli->radius = rad;
	printf("obj cyli created\n");
	return (&obj_cyli->base);
}
