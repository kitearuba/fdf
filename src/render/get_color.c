/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:34:28 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static int	clamp_ratio(float ratio)
{
	if (ratio < 0.0)
		return (0.0);
	if (ratio > 1.0)
		return (1.0);
	return (ratio);
}

int	interpolate_color(int low_color, int high_color, float ratio)
{
	int	red, green, blue;

	ratio = clamp_ratio(ratio);  // Ensures ratio stays within [0.0, 1.0]

	red = ((low_color >> 16) & 0xFF) + ratio * (((high_color >> 16) & 0xFF) - ((low_color >> 16) & 0xFF));
	green = ((low_color >> 8) & 0xFF) + ratio * (((high_color >> 8) & 0xFF) - ((low_color >> 8) & 0xFF));
	blue = (low_color & 0xFF) + ratio * ((high_color & 0xFF) - (low_color & 0xFF));

	// Ensure RGB values are in the valid range [0, 255]
	if (red < 0) red = 0;
	if (red > 255) red = 255;
	if (green < 0) green = 0;
	if (green > 255) green = 255;
	if (blue < 0) blue = 0;
	if (blue > 255) blue = 255;

	return ((red << 16) | (green << 8) | blue);
}

int	get_color(t_fdf *fdf, int z)
{
	float	ratio;

	if (fdf->max_z != fdf->min_z)
		return (fdf->low_color);
	ratio = (float)(z - fdf->min_z) / (fdf->max_z - fdf->min_z);
	return (interpolate_color(fdf->low_color, fdf->high_color, ratio));
}
static const int g_color_presets[NUM_COLOR_SCHEMES][2] = {
	{ICE_BLUE, LIGHT_GREEN},
	{MINT_GREEN, TEAL_BLUE},
	{RED, ORANGE},
	{PURPLE, PINK},
	{COOL_BLUE, SKY_BLUE},
	{DEFAULT_COLOR, TEAL_BLUE}
};

const int	*get_color_scheme(int index)
{
	return (g_color_presets[index]);
}
