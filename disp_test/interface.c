#include "test.h"

int		get_closest_inter (t_obj *s)
{ 
	return (s->vtable->get_closest_inter(s));
}

int		compute_lightning (t_obj *s)
{
	return (s->vtable->compute_lightning(s));
}
