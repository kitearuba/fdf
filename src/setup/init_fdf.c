/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/06 21:32:49 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  SET FIXED ZOOM  :::                           */
/*                                                                            */
/*   Function: set_fixed_zoom                                                 */
/*   Description: Determines the zoom level based on the map size.            */
/*                                                                            */
/*   - Calculates zoom based on window size and map dimensions.               */
/*   - Uses separate calculations for width and height.                       */
/*   - Selects the smaller zoom value to ensure the entire map fits.          */
/*   - Enforces a minimum zoom level of 1.                                    */
/*   - Limits the zoom to a maximum of 30 to prevent overscaling.             */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure where zoom is stored.            */
/*   @param map Pointer to the map structure to determine its size.           */
/*                                                                            */
/* ************************************************************************** */

static void	set_fixed_zoom(t_fdf *fdf, t_map *map)
{
	float	zoom_x;
	float	zoom_y;

	zoom_x = fdf->win_width / (map->width * 1.5);
	zoom_y = fdf->win_height / (map->height * 1.5);
	fdf->zoom = zoom_x;
	if (zoom_y < zoom_x)
		fdf->zoom = zoom_y;
	if (fdf->zoom < 1)
		fdf->zoom = 1;
	if (fdf->zoom > 30)
		fdf->zoom = 30;
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  SET OFFSET  :::                               */
/*                                                                            */
/*   Function: set_offset                                                     */
/*   Description: Centers the map within the window by adjusting offsets.     */
/*                                                                            */
/*   - Computes the center of the map based on width, height, and zoom.       */
/*   - Uses different calculations for isometric and parallel projections.    */
/*   - Ensures proper centering of both small and large maps.                 */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure where offsets are stored.        */
/*   @param map Pointer to the map structure to determine positioning.        */
/*                                                                            */
/* ************************************************************************** */
static void	set_offset(t_fdf *fdf, t_map *map)
{
	int	center_x;
	int	center_y;

	if (fdf->projections == 0)
	{
		center_x = ((map->width - 1) - (map->height - 1)) * fdf->zoom / 2;
		center_y = ((map->width - 1) + (map->height - 1)) * fdf->zoom / 4;
		fdf->offset_x = fdf->win_width / 2;
		fdf->offset_x -= center_x;
		fdf->offset_y = fdf->win_height / 2;
		fdf->offset_y -= center_y;
	}
	else
	{
		fdf->offset_x = fdf->win_width / 2;
		fdf->offset_x -= (map->width * fdf->zoom) / 2;
		fdf->offset_y = fdf->win_height / 2;
		fdf->offset_y -= (map->height * fdf->zoom) / 2;
	}
}

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
		parse_error("Error: Memory allocation failed for FDF", 0, map);
	ft_memset(fdf, 0, sizeof(t_fdf));
	fdf->low_color = DEFAULT_COLOR;
	fdf->high_color = LIGHT_GREEN;
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
