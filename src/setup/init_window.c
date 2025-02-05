/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_window.c                                       :+:      :+:    :+:   */
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
/*                         :::  SET WINDOW SIZE  :::                          */
/*                                                                            */
/*   Function: set_window_size                                                */
/*   Description: Defines the default window dimensions for rendering.        */
/*                                                                            */
/*   - Sets the window width to MACRO WIN_WIDTH.                                  */
/*   - Sets the window height to MACRO WIN_HEIGHT.                                 */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure where window size is stored.     */
/*                                                                            */
/* ************************************************************************** */
void	set_window_size(t_fdf *fdf)
{
	fdf->win_width = WIN_WIDTH;
	fdf->win_height = WIN_HEIGHT;
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  SET FIXED ZOOM  :::                           */
/*                                                                            */
/*   Function: set_fixed_zoom                                                 */
/*   Description: Determines the zoom level based on the map size.            */
/*                                                                            */
/*   - Uses a base zoom level of 20 for small maps.                           */
/*   - Adjusts zoom dynamically for larger maps to maintain visibility.       */
/*   - If the map's largest dimension exceeds 100, reduces zoom to 5.         */
/*   - If the largest dimension exceeds 50 but is below 100, sets zoom to 10. */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure where zoom is stored.            */
/*   @param map Pointer to the map structure to determine its size.           */
/*                                                                            */
/* ************************************************************************** */
void	set_fixed_zoom(t_fdf *fdf, t_map *map)
{
	int	max_size;

	max_size = map->width;
	if (map->height > map->width)
		max_size = map->height;
	fdf->zoom = 20;
	if (max_size > 100)
		fdf->zoom = 5;
	else if (max_size > 50)
		fdf->zoom = 10;
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  SET OFFSET  :::                               */
/*                                                                            */
/*   Function: set_offset                                                     */
/*   Description: Centers the map within the window by adjusting offsets.     */
/*                                                                            */
/*   - Computes the center of the map based on width, height, and zoom.       */
/*   - Adjusts offset_x and offset_y to position the map in the center.       */
/*   - Ensures correct centering for different map sizes.                     */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure where offsets are stored.        */
/*   @param map Pointer to the map structure to determine positioning.        */
/*                                                                            */
/* ************************************************************************** */
void	set_offset(t_fdf *fdf, t_map *map)
{
	int	center_x;
	int	center_y;

	center_x = ((map->width - 1) - (map->height - 1)) * fdf->zoom / 2;
	center_y = ((map->width - 1) + (map->height - 1)) * fdf->zoom / 4;
	fdf->offset_x = fdf->win_width / 2 - center_x;
	fdf->offset_y = fdf->win_height / 2 - center_y;
}
