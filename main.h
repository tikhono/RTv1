#ifndef MAIN_H
# define MAIN_H
# define WIDTH 555
//with even numbers last right vertical column appear on other side of img
# define HEIGHT 555
# define BACKGROUND 0

# include <math.h>
# include <stdio.h>
# include <mlx.h>
# include "./libft/libft.h"

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_sphere
{
	t_vec3		center;
	double		radius;
	int			color;
}				t_sphere;

typedef struct	s_data
{
	int			arr_lenth;
	double		viewport_size;
	double		projection_plane_z;
	t_vec3		camera_pos;
	t_vec3		direction;
	t_sphere	*arr;
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
t_vec3			substract(t_vec3 a, t_vec3 b);

#endif
