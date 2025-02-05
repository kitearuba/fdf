/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/04 22:55:22 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  UPDATE OFFSET  :::                            */
/*                                                                            */
/*   Function: update_offset                                                  */
/*   Description: Adjusts the map's position based on arrow key inputs.       */
/*                                                                            */
/*   - Moves the map left, right, up, or down based on key presses.           */
/*   - Updates either the X or Y offset accordingly.                          */
/*   - Flags the frame as updated if any movement occurs.                     */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing map settings.         */
/*   @param updated Pointer to the flag indicating if an update occurred.     */
/*                                                                            */
/* ************************************************************************** */
static void	update_offset(t_fdf *fdf, int *updated)
{
	const int	offset_keys[] = {1, 2, 3, 4};
	const int	offset_values[] = {-2, 2, -2, 2};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (fdf->key_pressed[offset_keys[i]])
		{
			if (i < 2)
				fdf->offset_x += offset_values[i];
			else
				fdf->offset_y += offset_values[i];
			*updated = 1;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  UPDATE ZOOM & ROTATION  :::                   */
/*                                                                            */
/*   Function: update_zoom_rotation                                           */
/*   Description: Modifies zoom level and rotation angles based on input.     */
/*                                                                            */
/*   - Adjusts zoom level when zoom in/out keys are pressed.                  */
/*   - Rotates the map along the X, Y, or Z axis based on rotation keys.      */
/*   - Flags the frame as updated if any changes occur.                       */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing map settings.         */
/*   @param updated Pointer to the flag indicating if an update occurred.     */
/*                                                                            */
/* ************************************************************************** */
static void	update_zoom_rotation(t_fdf *fdf, int *updated)
{
	const int	keys[] = {5, 6, 7, 8, 9, 10, 11, 12};
	const float	changes[] = {0.2, -0.2, 1, -1, -1, 1, -1, 1};
	int			i;

	i = 0;
	while (i < 8)
	{
		if (fdf->key_pressed[keys[i]])
		{
			if (i < 2)
				fdf->zoom += changes[i];
			else if (i < 4)
				fdf->rotation_x += changes[i];
			else if (i < 6)
				fdf->rotation_y += changes[i];
			else
				fdf->rotation_z += changes[i];
			*updated = 1;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  UPDATE PROJECTION & THICKNESS  :::            */
/*                                                                            */
/*   Function: update_projection_and_l_thickness                              */
/*   Description: Updates the projection mode and line thickness.             */
/*                                                                            */
/*   - Switches between isometric and parallel projections.                   */
/*   - Increases or decreases line thickness within the allowed range.        */
/*   - Flags the frame as updated if any changes occur.                       */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing projection settings.  */
/*   @param updated Pointer to the flag indicating if an update occurred.     */
/*                                                                            */
/* ************************************************************************** */
static void	update_projection_and_l_thickness(t_fdf *fdf, int *updated)
{
	if (fdf->key_pressed[13])
	{
		fdf->projections = 0;
		*updated = 1;
	}
	if (fdf->key_pressed[14])
	{
		fdf->projections = 1;
		*updated = 1;
	}
	if (fdf->key_pressed[15] && fdf->line_thickness < 30)
	{
		fdf->line_thickness += 1;
		*updated = 1;
	}
	if (fdf->key_pressed[16] && fdf->line_thickness > 1)
	{
		fdf->line_thickness -= 1;
		*updated = 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  UPDATE COLOR  :::                             */
/*                                                                            */
/*   Function: update_color                                                   */
/*   Description: Changes the map's color theme based on key input.           */
/*                                                                            */
/*   - Resets colors to default when the reset key is pressed.                */
/*   - Changes the color gradient between predefined color sets.               */
/*   - Flags the frame as updated if any color change occurs.                  */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing color settings.       */
/*   @param updated Pointer to the flag indicating if an update occurred.     */
/*                                                                            */
/* ************************************************************************** */
static void	update_color(t_fdf *fdf, int *updated)
{
	if (fdf->key_pressed[17])
	{
		fdf->low_color = DEFAULT_COLOR;
		fdf->high_color = DEFAULT_COLOR;
		*updated = 1;
	}
	if (fdf->key_pressed[18])
	{
		fdf->low_color = PINK;
		fdf->high_color = MINT_GREEN;
		*updated = 1;
	}
	if (fdf->key_pressed[19])
	{
		fdf->low_color = SKY_BLUE;
		fdf->high_color = RED;
		*updated = 1;
	}
	if (fdf->key_pressed[20])
	{
		fdf->low_color = ICE_BLUE;
		fdf->high_color = ORANGE;
		*updated = 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  UPDATE FRAME  :::                             */
/*                                                                            */
/*   Function: update_frame                                                   */
/*   Description: Handles all user input updates and redraws the frame.       */
/*                                                                            */
/*   - Exits the program if the escape key is pressed.                        */
/*   - Updates projection mode, zoom, rotation, offset, and colors.           */
/*   - Calls render_fdf if any updates occurred.                              */
/*   - Displays the updated image using MiniLibX.                             */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rendering settings.   */
/*   @return Always returns 0 (for compatibility with MiniLibX hooks).        */
/*                                                                            */
/* ************************************************************************** */
int	update_frame(t_fdf *fdf)
{
	int	updated;

	updated = 0;
	if (fdf->key_pressed[0])
		handle_exit(fdf);
	update_projection_and_l_thickness(fdf, &updated);
	update_offset(fdf, &updated);
	update_zoom_rotation(fdf, &updated);
	update_color(fdf, &updated);
	if (updated)
		render_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	return (0);
}
