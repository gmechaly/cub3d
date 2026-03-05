# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 16:40:04 by gmechaly          #+#    #+#              #
#    Updated: 2025/07/30 22:17:47 by rdalal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES)
NAME = cub3D
INCLUDES = includes/
SRCS_PATH = srcs/
SRCS_PARSE_PATH = parsing/
SRCS_FILES = main.c frees.c inits.c draw.c draw_2d.c draw_3d.c utils.c input.c \
			move.c rays.c load_textures.c utils2.c
SRCS_PARSING =	map_utils.c map_utils2.c map_closed.c maps_parsing.c \
				parse_colors.c parse_textures.c parse_utils.c parse.c \
				player_init.c maps_parsing_main.c map_array.c  \
				parse_colors2.c parse_textures2.c parse_lines.c gun.c draw_gun.c
				
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES)) \
		$(addprefix $(SRCS_PARSE_PATH), $(SRCS_PARSING))
OBJ = $(SRCS:.c=.o)

LIBFT_H_PATH = libft/includes/
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

MLX = mlx/
MLXFLAGS = -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(LIBFT) :
	make -C $(LIBFT_PATH)
	make -C $(MLX)

$(NAME) : $(OBJ) $(LIBFT) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJ) -L$(MLX) -I$(MLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES) -I$(LIBFT_H_PATH) -I$(MLX)

clean:
	rm -rf $(OBJ)
	make clean -C $(LIBFT_PATH)
	make clean -C $(MLX)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)
	make clean -C $(MLX)

re: fclean all

.PHONY: clean fclean re all