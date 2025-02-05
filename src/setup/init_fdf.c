/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:54:55 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  INIT MLX WINDOW  :::                          */
/*                                                                            */
/*   Function: init_mlx_window                                                */
/*   Description: Initializes the MiniLibX instance and creates a window.     */
/*                                                                            */
/*   - Calls mlx_init to initialize MiniLibX.                                 */
/*   - Creates a new window with specified width and height.                  */
/*   - Handles errors by calling free_on_error if initialization fails.       */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing window settings.      */
/*                                                                            */
/* ************************************************************************** */
static void	init_mlx_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		free_on_error(fdf, "Error: Failed to initialize MiniLibX");
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_width, fdf->win_height, "FDF");
	if (!fdf->win)
		free_on_error(fdf, "Error: Failed to create window");
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  INIT IMAGE BUFFER  :::                        */
/*                                                                            */
/*   Function: init_image_buffer                                              */
/*   Description: Creates an image buffer for rendering the map.              */
/*                                                                            */
/*   - Calls mlx_new_image to create a new image in MiniLibX.                 */
/*   - Retrieves image data address and stores it in the FDF structure.       */
/*   - Handles errors by calling free_on_error if initialization fails.       */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing image settings.       */
/*                                                                            */
/* ************************************************************************** */
static void	init_image_buffer(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, fdf->win_width, fdf->win_height);
	if (!fdf->img.img)
		free_on_error(fdf, "Error: Failed to create image");
	fdf->img.addr = mlx_get_data_addr(fdf->img.img,
			&fdf->img.bits_per_pixel, &fdf->img.line_length, &fdf->img.endian);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  INIT FDF  :::                                 */
/*                                                                            */
/*   Function: init_fdf                                                       */
/*   Description: Initializes the main FDF structure and sets up rendering.   */
/*                                                                            */
/*   - Allocates memory for the FDF structure.                                */
/*   - Sets initial colors, zoom, and offsets based on the map.               */
/*   - Initializes the MiniLibX window and image buffer.                      */
/*   - Registers keyboard event hooks and loop hooks for interactivity.       */
/*   - Handles errors if memory allocation or initialization fails.           */
/*                                                                            */
/*   @param map Pointer to the parsed map structure.                          */
/*   @return Pointer to the initialized FDF structure.                        */
/*                                                                            */
/* ************************************************************************** */
t_fdf	*init_fdf(t_map *map)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		fatal_error("Error: Memory allocation failed for FDF");
	ft_memset(fdf, 0, sizeof(t_fdf));
	fdf->low_color = DEFAULT_COLOR;
	fdf->high_color = DEFAULT_COLOR;
	fdf->map = map;
	set_window_size(fdf);
	set_fixed_zoom(fdf, map);
	set_offset(fdf, map);
	init_mlx_window(fdf);
	init_image_buffer(fdf);
	mlx_hook(fdf->win, 17, 0, handle_exit, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, handle_key_press, fdf);
	mlx_hook(fdf->win, 3, 1L << 1, handle_key_release, fdf);
	mlx_loop_hook(fdf->mlx, update_frame, fdf);
	return (fdf);
}
