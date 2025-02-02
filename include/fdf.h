/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/02 23:03:20 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* ************************************************************************** */
/*                               Includes                                     */
/* ************************************************************************** */

# include <unistd.h>
# include <fcntl.h> // For open()
# include <stdlib.h> // For exit() and abs()
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"

/* ************************************************************************** */
/*                                  Macros                                    */
/* ************************************************************************** */

# define STDERR 2
# define ESC_KEY 65307
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define KEY_COUNT 20
# define DEFAULT_COLOR 0xFFFFFF
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_map
{
	int		**data;
	int		**colors;
	int		height;
	int		width;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		offset_x;
	int		offset_y;
	int		win_width;
	int		win_height;
	int		key_pressed[KEY_COUNT];
	int		min_z;
	int		max_z;
	int		projections;
	int		line_thickness;
	float	zoom;
	float	rotation_y;
	float	rotation_x;
	t_map	*map;
}	t_fdf;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}	t_point;

typedef struct s_line
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		color1;
	int		color2;
}				t_line;

typedef struct s_rotation
{
	float	rad_x;
	float	rad_y;
	float	tmp_x;
	float	tmp_y;
	float	tmp_z;
}	t_rotation;

/* ************************************************************************** */
/*                           Function Prototypes                              */
/* ************************************************************************** */

/* Parse */
int		parse_map(const char *filename, t_map *map);
int		validate_dimensions(const char *line, t_map *map);
int		parse_rows(int fd, t_map *map, int *row);
int		parse_strict_atoi(const char *str, char **args);

/* Error */
void	free_on_error(t_fdf *fdf, const char *error_message);
void	fatal_error(const char *msg);

/* Rendering */
t_fdf	*init_fdf(t_map *map);
void	set_window_size(t_fdf *fdf);
void	set_fixed_zoom(t_fdf *fdf, t_map *map);
void	set_offset(t_fdf *fdf, t_map *map);
void	render_fdf(t_fdf *fdf);
t_point	project_isometric(t_fdf *fdf, int x, int y, int z);
t_point	project_parallel(t_fdf *fdf, int x, int y, int z);
void	draw_thick_line(t_fdf *fdf, t_point p1, t_point p2);
int		handle_key_press(int key, t_fdf *fdf);
int		handle_key_release(int key, t_fdf *fdf);
int		update_frame(t_fdf *fdf);
int		get_color(int z, int min_z, int max_z);
int		update_frame(t_fdf *fdf);

/* Utils */
void	free_map(t_map *map);
void	free_fdf(t_fdf *fdf);
void	free_2d_array(char **arr);
int		handle_exit(t_fdf *fdf);
void	find_min_max_z(t_fdf *fdf);
int		handle_exit(t_fdf *fdf);

#endif //FDF_H
