#ifndef MAIN_H
# define MAIN_H
# define HEIGHT 777
# define WIDTH 777
# define BACKGROUND 16777215

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"

struct				s_all;
struct				s_interface;

typedef struct		s_inter
{
	double			one;
	double			two;
}					t_inter;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_obj
{
	struct s_interface	*const vtable;
}					t_obj;

typedef struct		s_interface
{
	t_inter			(*get_intersections)(struct s_all *a, t_obj *s, t_vec3 point, t_vec3 dir);
	t_vec3			(*get_normal)(t_obj *s, t_vec3 point, t_vec3 dir);
	t_vec3			(*get_color)(t_obj *s);
}					t_interface;

typedef struct		s_range
{
	double			min;
	double			max;
}					t_range;

typedef struct		s_light
{
	t_vec3			center;
	double			intensity;
}					t_light;

typedef struct		s_sphere
{
	t_obj			base;
	t_vec3			center;
	t_vec3			color;
	double			radius;
}					t_sphere;

typedef struct		s_plane
{
	t_obj			base;
	t_vec3			norm;
	t_vec3			color;
	double			dist;
}					t_plane;

typedef struct		s_cylinder
{
	t_obj			base;
	t_vec3			center;
	t_vec3			norm;
	t_vec3			color;
	double			radius;
}					t_cylinder;

typedef struct		s_cone
{
	t_obj			base;
	t_vec3			center;
	t_vec3			norm;
	t_vec3			color;
	double			angle;
}					t_cone;

typedef struct		s_clos
{
	double			dist;
	t_obj			*obj;
}					t_clos;

typedef struct		s_node
{
	t_obj			*obj;
	struct s_node	*next;
}					t_node;

typedef struct		s_data
{
	int				obj_arr_length;
	int				light_arr_length;
	char			*file;
	double			viewport_size;
	double			projection_plane_z;
	t_vec3			camera_pos;
	t_vec3			camera_dir;
	t_node			*obj_list;
	t_light			*light;
}					t_data;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int				x;
	int				y;
	int				z;
}					t_mlx;

typedef struct		s_all
{
	t_mlx			p;
	t_data			d;
	int				*addr;
}					t_all;

t_inter				get_intersections(t_all *a, t_obj *s, t_vec3 point, t_vec3 dir);
t_vec3				get_normal(t_obj *s, t_vec3 point, t_vec3 dir);
t_vec3				get_color(t_obj *s);

t_obj				*obj_cone_create (t_vec3 cent, t_vec3 norm, t_vec3 col, double angle);
t_obj				*obj_cyli_create (t_vec3 cent, t_vec3 norm, t_vec3 col, double rad);
t_obj				*obj_plane_create (t_vec3 norm, t_vec3 col, double dist);
t_obj				*obj_sphere_create (t_vec3 cent, t_vec3 col, double rad);

void				push_list(t_node **head, t_obj *obj);

int					get_int(int fd);
double				get_double(int fd);
t_vec3				get_vector(int fd);

void				get_cones(t_all *all, int fd);
void				get_planes(t_all *all, int fd);
void				get_spheres(t_all *all, int fd);
void				get_cylinders(t_all *all, int fd);
void				get_light(t_all *all, int fd);

int					call_hookers(int key, t_all *a);
int					exit_mouse(void);
int					convert_to_int(t_vec3 color);
void				init(t_all *a, char *file);
void				parse(t_all *a);
void				render(t_all *a);
void				put_pixel(t_all *a, int x, int y, int color);
void				trace_ray(t_all *a, int x, int y, t_vec3 direction);
t_clos				get_closest_inter(t_all *a, t_vec3 point, t_vec3 direction, t_range r);
double				product(t_vec3 a, t_vec3 b);
double				length(t_vec3 a);
t_vec3				normalize(t_vec3 a);
t_vec3				substract(t_vec3 a, t_vec3 b);
t_vec3				add(t_vec3 a, t_vec3 b);
t_vec3				multiply(t_vec3 a, double k);

#endif
