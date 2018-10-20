#include "test.h"

static int	get_closest_inter_cone (t_obj *s)
{
	printf("cone intersect was computed\n");
}

static int	compute_lightning_cone (t_obj *s)
{
	printf("cone lightning was computed\n");
}

t_obj	*obj_cone_create(t_vec3 cent, t_vec3 norm, t_vec3 col, double angle)
{
	static const t_interface vtable = {
		get_closest_inter_cone,
		compute_lightning_cone
	};
	static t_obj base = { &vtable };
	t_cone *sl = malloc(sizeof(*sl));
	memcpy(&sl->base, &base, sizeof(base));
	printf("obj cone created\n");
	return (&sl->base);
}


