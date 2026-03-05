/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:47:41 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/30 22:13:15 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

# define HSIZE 512
# define LSIZE 1024

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define CYAN 0x0000FFFF
# define YELLOW 0x00FFFF00
# define PURPLE 0x00FF00FF
# define WHITE 0x00FFFFFF
# define GRAY 0x00404040
# define BLACK 0x00000000

# define PI 3.1415926535
# define DEG 0.01745329252

# define GUN_FRAME_COUNT 4
# define GUN_FRAME_DELAY 8
# define BOB_HEIGHT 4
# define BREATH_AMPLITUDE 2
# define BREATH_SPEED 0.05

typedef struct s_gun
{
	void	*frames[GUN_FRAME_COUNT];
	int		current_frame;
	int		frame_delay;
	int		frame_timer;
	int		width;
	int		height;
	int		frame_count;
	double	breath_phase;
	bool	is_walking;
	int		bpp;
	int		size_line;
	int		endian;
	int		transp;
}			t_gun;

typedef struct s_map
{
	char		**map;
	char		*texture_no;
	char		*texture_so;
	char		*texture_we;
	char		*texture_ea;
	char		*texture_door;
	int			floor_color;
	int			ceiling_color;
	int			width;
	int			height;
	int			tile_size;
}				t_map;

typedef struct s_ray
{
	int		hit;
	int		side;
	float	ddx;
	float	ddy;
	float	sdx;
	float	sdy;
	float	hdist;
	float	dx;
	float	dy;
	float	ray_size;
	int		wall_size;
	float	ray_angle;
	int		x_bwall;
	int		y_bwall;
}			t_ray;

typedef struct s_player
{
	t_map	*map;
	float	px;
	float	py;
	float	dx;
	float	dy;
	float	angle;
	float	rx;
	float	ry;
	float	xoff;
	float	yoff;
	int		mapx;
	int		mapy;
	int		move_straight;
	int		move_side;
	int		rotate;
	int		mouse_moved;
	int		e_pressed;
}			t_player;

typedef struct s_img
{
	void		*image;
	void		*ptr_image;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct s_tex
{
	t_img	*img_struct;
	int		wall_width;
	int		wall_height;
	int		orientation;
}				t_tex;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_img		*win_img;
	t_img		*map_img;
	t_tex		*north;
	t_tex		*south;
	t_tex		*east;
	t_tex		*west;
	t_tex		*door;
	t_gun		gun;
	int			color;
	t_player	*player;
	t_map		*map;
}				t_data;

/***draw_3d***/
void	compute_wall_3d(t_data *data, t_ray *ray, int i);

/***draw_2d***/
void	draw_background(t_data *data);
// void	draw_player(t_data *data);
void	draw_minimap(t_data *data);
// void	draw_window(t_data *data);

/***draw***/
int		draw(t_data *data);
void	draw_line_from_player(int xb, int yb, t_data *data);

/***frees***/
int		quit_program(t_data *data);
void	free_map_array(char **map);

/***inits***/
void	*init_mlx(t_data *data);
void	create_window(t_data *data);
t_map	*init_map_file(t_data *data, char *filename);

/***input***/
int		e_press(t_data *data);
void	handle_input(t_data *data);

/***load_textures***/
int		get_right_orientation(t_data *data, t_ray *ray);
void	*load_textures(t_data *data);
t_tex	*load_one_texture(t_data *data, char *path_to_texture, int orientation);

/***move***/
int		move_player(t_data *data);
int		move_angle(t_data *data, float da);

/***ray***/
void	*cast_rays(t_data *data);

/***utils***/
void	*ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void	copy_image(t_img *src, t_img *dst, int width, int height);
int		is_valid_coordinates(int x, int y);
float	min(float a, float b);
int		get_texture_pixel(t_tex *texture, int x, int y);

/***utils2***/
int		is_wall(int x, int y, t_map *map);

/***parse***/
int		parse_file(char *filename, t_map *map);
void	append_to_map(char **map_str, char *line);
int		process_texture_colors(char *trimmed, t_map *map);
int		process_line(char *line, t_map *map, bool *in_map, char **map_str);

/***parse_utils***/
void	ft_free_split(char **split);
bool	all_textures_defined(t_map *map);
bool	all_colors_defined(t_map *map);

/***parse_textures***/
bool	is_texture_line(char *line);
void	remove_trailing_newline(char *line);
int		dup_check(t_map *map, char *id, char *path);
int		parse_texture_line(char *line, t_map *map);

/***parse_colors***/
bool	is_color_line(char *line);
bool	is_valid_rgb_value(int val);
int		rgb_to_int(int r, int g, int b);
int		parse_color_line(char *line, t_map *map);
int		check_rgb_split(char **rgb);

/***map_utils***/
bool	validate_full_map(t_map *map);
bool	is_enclosed(t_map *map);
bool	out_of_bounds(t_map *map, int y, int x);
char	**create_map_array(int fd);
int		count_map_rows(t_map *map);
int		longest_row_len(t_map *map);
int		is_valid_fill_char(char c);

/***map_parsing***/
bool	valid_map(char *line);
char	**parse_map(char *path, t_map *map);
void	append_line_to_map(t_map *map, char *line);

/***map_validation***/
bool	validate_map(t_map *map);

/***player_init***/
int		init_player_from_map(t_player *plyr);

/***gun***/
void	init_gun(t_gun *gun, void *mlx);
void	update_gun_animation(t_gun *gun);
int		get_transparent_color(void *img);
void	draw_gun(t_gun *gun, t_img *win_img);
#endif