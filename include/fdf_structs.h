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

/* ************************************************************************** */
/*                           Map Structure                                    */
/* ************************************************************************** */

typedef struct s_map
{
	int		**data;     // Height values of the map
	int		**colors;   // Color values for each point (if provided)
	int		height;     // Number of rows in the map
	int		width;      // Number of columns in the map
}	t_map;

/* ************************************************************************** */
/*                           Image Structure                                  */
/* ************************************************************************** */

typedef struct s_img
{
	void	*img;           // Pointer to the image in MiniLibX
	char	*addr;          // Address of the image data
	int		bits_per_pixel; // Number of bits per pixel
	int		line_length;    // Length of a line in bytes
	int		endian;         // Endian format (big or little endian)
}	t_img;

/* ************************************************************************** */
/*                           Main FDF Structure                               */
/* ************************************************************************** */

typedef struct s_fdf
{
	void	*mlx;              // MiniLibX connection pointer
	void	*win;              // MiniLibX window pointer
	t_img	img;               // Image structure for rendering
	int		offset_x;         // X-axis offset for centering
	int		offset_y;         // Y-axis offset for centering
	int		win_width;        // Window width
	int		win_height;       // Window height
	int		key_pressed[KEY_COUNT]; // Array tracking key states
	int		projections;      // Projection mode (0 = isometric, 1 = parallel)
	int		line_thickness;   // Thickness of rendered lines
	int		color_index;      // Index for selecting color schemes
	int		low_color;        // Low altitude color
	int		high_color;       // High altitude color
	float	min_z;            // Minimum Z value in the map
	float	max_z;            // Maximum Z value in the map
	float	zoom;             // Zoom level for scaling
	float	rotation_y;       // Rotation angle along Y-axis
	float	rotation_x;       // Rotation angle along X-axis
	float	rotation_z;       // Rotation angle along Z-axis
	t_map	*map;             // Pointer to the map structure
}	t_fdf;

/* ************************************************************************** */
/*                           Point Structure                                  */
/* ************************************************************************** */

typedef struct s_point
{
	int		x;       // X coordinate
	int		y;       // Y coordinate
	int		z;       // Z coordinate (height)
	int		color;   // Color value
}	t_point;

/* ************************************************************************** */
/*                           Line Structure                                   */
/* ************************************************************************** */

typedef struct s_line
{
	int		dx;       // Change in X direction
	int		dy;       // Change in Y direction
	int		sx;       // Step in X direction
	int		sy;       // Step in Y direction
	int		err;      // Bresenham algorithm error term
	int		e2;       // Double error term for pixel updates
	int		color1;   // Color at the start of the line
	int		color2;   // Color at the end of the line
	float	steps;    // Number of steps for interpolation
}	t_line;

/* ************************************************************************** */
/*                           Rotation Structure                               */
/* ************************************************************************** */

typedef struct s_rotation
{
	float	rad_x;    // Rotation angle in radians (X-axis)
	float	rad_y;    // Rotation angle in radians (Y-axis)
	float	rad_z;    // Rotation angle in radians (Z-axis)
	float	tmp_x;    // Temporary X coordinate
	float	tmp_y;    // Temporary Y coordinate
	float	tmp_z;    // Temporary Z coordinate
	float	final_x;  // Final X coordinate after rotation
	float	final_y;  // Final Y coordinate after rotation
}	t_rotation;

#endif /* FDF_STRUCTS_H */
