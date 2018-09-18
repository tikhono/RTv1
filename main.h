#ifndef MAIN_H
# define MAIN_H
# include <math.h>
# include <stdio.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"

typedef struct	s_vec3
{
	int			x;
	int			y;
	int			z;
}				t_vec3;

typedef struct	s_sphere
{
	t_vec3		center;
	int			radius;
	int			color;
}				t_sphere;

typedef struct	s_data
{
	int			width;
	int			height;
	int			background_color;
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
	int			*addr;
}				t_mlx;

typedef struct	s_all
{
	t_mlx		*p;
	t_data		*d;
	int			*addr;
}				t_all;

int				call_hookers(int key, t_all *a);
int				exit_mouse(void);

int				product(t_vec3 a, t_vec3 b);
t_vec3			substract(t_vec3 a, t_vec3 b);

#endif
