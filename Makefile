# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 18:40:56 by ilmira            #+#    #+#              #
#    Updated: 2021/04/09 10:51:25 by ilmira           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
SRC_DIR = ./src/
SRCF =	main.c\
		error.c\
		error2.c\
		error3.c\
		ft_board.c\
		ft_con.c\
		ft_cylinder.c\
		ft_light.c\
		ft_normal.c\
		ft_plane.c\
		ft_rot.c\
		ft_sphere.c\
		ft_trace.c\
		parser.c\
		parse_cam.c\
		parse_cone.c\
		parse_cylinder.c\
		parse_light.c\
		parse_plane.c\
		parse_sphere.c\
		texture.c\
		transperency.c\
		ft_json.c\
		solve_4.c\
		parse_paraboloid.c\
		paraboloid.c\
		torus.c\
		solve_3.c\
		parse_torus.c\
		parse_cube.c\
		sdl_thread.c\
		perlin.c\
		screenshot.c\
		texture_map.c\
		ft_light1.c\
		cube.c\
		quadratic_equation.c\
		check_intersect.c\
		ft_check.c\
		parse_texture.c\
		perandom.c\
		perandom2.c\
		perandom3.c\
		copy_thread.c\
		ft_shadow.c\
		ft_shadow1.c\
		limit.c\
		stereoscopy.c\
		blur.c\
		visual_filters.c\
		new_texture.c\
		menu.c\
		menu_utils.c\
		keys.c\
		init.c\
		path.c\
		rotate_vec.c

OBJ_DIR = ./obj/
SRC = $(addprefix $(SRC_DIR), $(SRCF))
OBJ = $(addprefix $(OBJ_DIR), $(OBJF))
OBJF = $(SRCF:.c=.o)
LIBS = libft/libft.a veclib/veclib.a json-c/libjson-c.a
HEADERS = -I ./includes -I ./libft -I ./veclib -I ./json-c
HDR = includes/rt.h
FLAGS = -Wall -Wextra -Werror -g
CGFLAGS =  -framework OpenGL -framework AppKit
INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks/
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer

all: obj $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(NAME): libft/libft.a veclib/veclib.a json-c/libjson-c.a $(OBJ) $(HDR)
	@gcc $(FLAGS) $(CGFLAGS) $(FRAMEWORKS) $(OBJ) $(LIBS) -o $(NAME)
	@printf '\033[32m[ ✔ ] %s\n\033[0m' "Create RT"

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HDR)
	@gcc $(FLAGS) $(INCLUDES) $(HEADERS) -c $< -o $@
	@printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

clean:
	@make clean -C libft
	@make clean -C veclib
	@rm -Rf $(OBJ)
	@rm -Rf obj
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean RT"

fclean: clean
	@make fclean -C libft
	@make fclean -C veclib
	@rm -rf $(NAME)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "All objects and binary of RT was deleted"

libft/libft.a:
	@make -C libft

veclib/veclib.a:
	@make -C veclib

json-c/libjson-c.a:
	@cd json-c
	@cmake CMakeLists.txt
	make
	cd ..

re: fclean all