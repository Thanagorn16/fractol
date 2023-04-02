# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 13:29:28 by truangsi          #+#    #+#              #
#    Updated: 2023/04/02 14:45:17 by truangsi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
MLX_FLAG = -Lmlx -lmlx -framework OpenGL -framework Appkit

NAME = fractol

#LIBFT_PATH = libft/

MLX_PATH = mlx/

#LIBFT_SRCS = ft_strlen.c ft_split.c ft_putstr_fd.c ft_strdup.c ft_atoi.c

FRACT_SRCS = fractol.c

#OBJS = $(SRCS:.c=.o)
OBJS = $(FRACT_SRCS:.c=.o)

all: $(NAME)

%o:%c
	gcc $(FLAGS) -Imlx -c $< -o $@

$(NAME): $(OBJS)
	gcc $(OBJS) $(FLAGS) $(MLX_FLAG) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus