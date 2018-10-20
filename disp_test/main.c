#include "test.h"

void	set_params(t_vec3 *a, t_vec3 *b, t_vec3 *c, double *d)
{
	a->x = 1;
	a->y = 2;
	a->z = 3;
	b->x = 4;
	b->y = 5;
	b->z = 6;
	c->x = 7;
	c->y = 8;
	c->z = 9;
	*d = 0;
}

int		main(void)
{
	t_vec3	a;//made it one structure
	t_vec3	b;
	t_vec3	c;
	double	d;
	set_params(&a, &b, &c, &d);
	struct s_obj *s1 = obj_cyli_create(a, b, c, d);
	struct s_obj *s2 = obj_cone_create(a, b, c, d);

	get_closest_inter(s1);
	get_closest_inter(s2);
	compute_lightning(s1);
	compute_lightning(s2);
	return (0);
}

