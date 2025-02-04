/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:00:00 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/03 12:30:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCTS_H
# define FDF_STRUCTS_H

# include "fdf_macros.h"

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
	int		projections;
	int		line_thickness;
	int		color_index;
	int		low_color;
	int		high_color;
        float	min_z;
        float 	max_z;
	float	zoom;
	float	rotation_y;
	float	rotation_x;
	float	rotation_z;
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
	float	steps;
}	t_line;

typedef struct s_rotation
{
	float	rad_x;
	float	rad_y;
	float	rad_z;
	float	tmp_x;
	float	tmp_y;
	float	tmp_z;
	float	final_x;
	float	final_y;
}	t_rotation;

#endif // FDF_STRUCTS_H
