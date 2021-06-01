# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/30 13:02:53 by ilmira            #+#    #+#              #
#    Updated: 2021/03/30 13:02:53 by ilmira           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = veclib.a

FLAGS = -Wall -Wextra -Werror

SRC = \
	vec_dot.c\
	vec_len.c\
	vec_norm.c\
	vec_scale.c\
	vec_sub.c\
	vec_sum.c\
	vec_rotx.c\
	vec_roty.c\
	vec_rotz.c\
	vec_rot.c\
	vec_mult.c

OBJ = $(SRC:.c=.o)
HEADER = veclib.h

all: $(NAME)

$(NAME):$(OBJ) $(HEADER)
	@ar rc $(NAME) $(OBJ) $(HEADER)
	@ranlib $(NAME)


%.o : %.c $(HEADER)
	@gcc $(SRC) $(FLAGS) -c -I $(HEADER) $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
