#include "main.h"

int		product(t_vec3 a, t_vec3 b)
{
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

t_vec3	substract(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}
