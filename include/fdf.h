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
# include "fdf_structs.h"

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
t_point	apply_isometric(t_fdf *fdf, int x, int y, int z);
t_point	apply_parallel(t_fdf *fdf, int x, int y, int z);
void	draw_line(t_fdf *fdf, t_point p1, t_point p2);
void	draw_thick_line(t_fdf *fdf, t_point p1, t_point p2);
int		handle_key_press(int key, t_fdf *fdf);
int		handle_key_release(int key, t_fdf *fdf);
int		update_frame(t_fdf *fdf);
int		get_color(t_fdf *fdf, int z);
const int	*get_color_scheme(int index);
void	bresenham_draw(t_fdf *fdf, t_point p1, t_point p2, t_line *line);

/* Utils */
void	free_map(t_map *map);
void	free_fdf(t_fdf *fdf);
void	free_2d_array(char **arr);
int		handle_exit(t_fdf *fdf);
void	find_min_max_z(t_fdf *fdf);
int		handle_exit(t_fdf *fdf);

#endif //FDF_H
