# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atikhono <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/01 17:15:51 by atikhono          #+#    #+#              #
#    Updated: 2018/10/25 14:58:08 by atikhono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

LIBNAME = ./libft/libft.a

OBJ = $(SRC:.c=.o)

FLAGS = -Wfatal-errors

#-Wall -Wextra -Werror

MLX = -lmlx -framework AppKit -framework OpenGL  

SRC =	main.c\
		hookers.c\
		cone.c\
		cylinder.c\
		sphere.c\
		plane.c\
		vec_comp.c\
		interface.c\
		parser.c\
		get_data.c\
		other.c\
		init.c
		

all: liball $(NAME)

obj: $(OBJ)

$(NAME) : $(LIBNAME) $(OBJ)
		gcc $(FLAGS) $^ -o $(NAME) $(MLX) $(OPENCL)

%.o: %.c
		gcc $(FLAGS) -o $@ -c $<

clean: libclean
		rm -rf $(OBJ)

fclean: libfclean clean
		rm -rf $(NAME)

re: fclean all

$(LIBNAME): liball

liball:
	@make -C ./libft all --silent

libclean:
	@make -C ./libft clean --silent

libfclean:
	@make -C ./libft fclean --silent

libre: libfclean liball
