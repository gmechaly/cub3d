/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:45:38 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/29 00:09:43 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exit_with_error(char *msg, t_data *data)
{
	if (msg)
		printf("Error: %s\n", msg);
	quit_program(data);
	exit(EXIT_FAILURE);
}

static void	init_every_data_to_null(t_data *data)
{
	int	i;

	i = -1;
	data->win_img = NULL;
	data->map_img = NULL;
	data->mlx = NULL;
	data->window = NULL;
	data->north = NULL;
	data->south = NULL;
	data->east = NULL;
	data->west = NULL;
	data->door = NULL;
	data->player = NULL;
	data->map = NULL;
	while (i < GUN_FRAME_COUNT)
		data->gun.frames[++i] = NULL;
}

static void	*parsing_main(int argc, char **argv)
{
	t_data		*data;
	t_map		*map;

	if (argc != 2 || !ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		exit_with_error("Usage: ./cub3D <map.cub>", NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		exit_with_error("Failed to allocate memory for data", NULL);
	init_every_data_to_null(data);
	map = init_map_file(data, argv[1]);
	if (!map)
		exit_with_error("Failed to initialize map", data);
	if (!init_mlx(data))
		exit_with_error("Failed to initialize MLX", data);
	init_gun(&data->gun, data->mlx);
	if (parse_file(argv[1], map) == -1)
		exit_with_error("Failed to parse config file", data);
	data->map = map;
	if (!validate_map(map))
		exit_with_error("Map validation failed", data);
	data->player->map = map;
	data->map = map;
	if (init_player_from_map(data->player) == -1)
		exit_with_error("Failed to initialize player position", data);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	data = parsing_main(argc, argv);
	if (!data)
		quit_program(data);
	load_textures(data);
	draw(data);
	handle_input(data);
	mlx_loop_hook(data->mlx, draw, data);
	mlx_hook(data->window, 17, 0L, quit_program, data);
	mlx_loop(data->mlx);
	quit_program(data);
	return (0);
}
