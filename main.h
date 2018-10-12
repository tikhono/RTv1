#ifndef MAIN_H
# define MAIN_H
# define WIDTH 777
//with even numbers last right vertical column appear on other side of img
# define HEIGHT 777
# define BACKGROUND 16777215

# include <math.h>
# include <stdio.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"

typedef struct	s_inter
{
	double		one;
	double		two;
}
				t_inter;

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_light
{
	t_vec3		center;
	double		intensity;
}				t_light;

typedef struct	s_plane
{
	t_vec3		norm;
	t_vec3		color;
	double		dist;
}
				t_plane;

typedef struct	s_sphere
{
	t_vec3		center;
	t_vec3		color;
	double		radius;
}				t_sphere;

typedef struct	s_data
{
	int			obj_arr_length;
	int 		light_arr_length;
	double		viewport_size;
	double		projection_plane_z;
	t_vec3		camera_pos;
	t_sphere	*arr;
	t_plane		*plane_arr;
	t_light		*light;
}				t_data;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	int			x;
	int			y;
	int			z;
}				t_mlx;

typedef struct	s_all
{
	t_mlx		p;
	t_data		d;
	int			*addr;
}				t_all;

int				call_hookers(int key, t_all *a);
int				exit_mouse(void);
double			product(t_vec3 a, t_vec3 b);
double 			length(t_vec3 a);
t_vec3			substract(t_vec3 a, t_vec3 b);
t_vec3			add(t_vec3 a, t_vec3 b);
t_vec3			multiply(t_vec3 a, double k);

#endif
