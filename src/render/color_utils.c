/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:45:25 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/05 21:54:37 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  CLAMP RATIO  :::                              */
/*                                                                            */
/*   Function: clamp_ratio                                                    */
/*   Description: Restricts a floating-point value within the range [0,1].    */
/*                                                                            */
/*   - Ensures the ratio does not fall below 0.0 or exceed 1.0.               */
/*   - Helps maintain proper color interpolation without overflow.            */
/*                                                                            */
/*   @param ratio The input ratio to clamp.                                   */
/*   @return The clamped ratio value.                                         */
/*                                                                            */
/* ************************************************************************** */
float	clamp_ratio(float ratio)
{
	if (ratio < 0.0f)
		return (0.0f);
	if (ratio > 1.0f)
		return (1.0f);
	return (ratio);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  INTERPOLATE COLOR  :::                        */
/*                                                                            */
/*   Function: interpolate_color                                              */
/*   Description: Blends two colors based on a ratio between 0 and 1.         */
/*                                                                            */
/*   - Extracts the red, green, and blue components of both colors.           */
/*   - Interpolates each color channel separately based on the given ratio.   */
/*   - Ensures the final RGB values remain within the valid range (0-255).    */
/*                                                                            */
/*   @param low_color The starting color.                                     */
/*   @param high_color The ending color.                                      */
/*   @param ratio The interpolation ratio (0 = low_color, 1 = high_color).    */
/*   @return The interpolated color as an integer.                            */
/*                                                                            */
/* ************************************************************************** */
int	interpolate_color(int low_color, int high_color, float ratio)
{
	int	red;
	int	green;
	int	blue;

	ratio = clamp_ratio(ratio);
	red = ((low_color >> 16) & 0xFF) + ratio * (((high_color >> 16) & 0xFF)
			- ((low_color >> 16) & 0xFF));
	green = ((low_color >> 8) & 0xFF) + ratio * (((high_color >> 8) & 0xFF)
			- ((low_color >> 8) & 0xFF));
	blue = (low_color & 0xFF) + ratio * ((high_color & 0xFF)
			- (low_color & 0xFF));
	if (red < 0)
		red = 0;
	if (red > 255)
		red = 255;
	if (green < 0)
		green = 0;
	if (green > 255)
		green = 255;
	if (blue < 0)
		blue = 0;
	if (blue > 255)
		blue = 255;
	return ((red << 16) | (green << 8) | blue);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  GET COLOR  :::                                */
/*                                                                            */
/*   Function: get_color                                                      */
/*   Description: Determines the color for a given Z value.                   */
/*                                                                            */
/*   - Maps the Z value to a color gradient between low_color and high_color. */
/*   - Uses linear interpolation based on the Z range of the map.             */
/*   - Ensures the ratio is properly clamped to avoid color distortion.       */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing color settings.       */
/*   @param z The height (Z value) for which the color is determined.         */
/*   @return The computed color as an integer.                                */
/*                                                                            */
/* ************************************************************************** */
int	get_color(t_fdf *fdf, int z)
{
	float	ratio;

	ratio = 0;
	if (fdf->max_z == fdf->min_z)
		return (fdf->high_color);
	ratio = (z - fdf->min_z) / (fdf->max_z - fdf->min_z);
	ratio = clamp_ratio(ratio);
	return (interpolate_color(fdf->low_color, fdf->high_color, ratio));
}
