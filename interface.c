#include "main.h"

t_inter	get_intersections (t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{ 
	return (s->vtable->get_intersections(a, s, point, dir));
}

t_vec3	compute_lightning (t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{
	return (s->vtable->compute_lightning(a, s, point, dir));
}
