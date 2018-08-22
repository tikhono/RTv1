/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:41:57 by atikhono          #+#    #+#             */
/*   Updated: 2018/08/22 11:25:32 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include "./libft/libft.h"

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	int					*addr;
}						t_mlx;

typedef struct			s_data
{
	int					width;
	int					height;
	int					m_pos_x;
	int					m_pos_y;
	int					lim;
	double				power;
	double				scale;
	double				off_x;
	double				off_y;
	char				sign_x;
	char				sign_y;
	char				abs_x;
	char				abs_y;
	char				constant;
	char				state;
}						t_data;

typedef struct			s_all
{
	t_mlx				p;
	t_data				d;
}						t_all;

int						call_hookers(int key, t_all *a);
int						mouse_click(int key, int x, int y, t_all *a);
int						mouse_move(int x, int y, t_all *a);
int						exit_mouse(void);

#endif
