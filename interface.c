#include "main.h"

t_inter	get_intersections(t_all *a, t_obj *s, t_vec3 point, t_vec3 dir)
{ 
	return (s->vtable->get_intersections(a, s, point, dir));
}

t_vec3	get_normal(t_obj *s, t_vec3 point, t_vec3 dir)
{
	return (s->vtable->get_normal(s, point, dir));
}

t_vec3	get_color(t_obj *s)
{
	return (s->vtable->get_color(s));
}
