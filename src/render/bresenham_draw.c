/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:45:25 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/04 20:55:24 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static float	clamp_ratio(float ratio)
{
	if (ratio < 0.0f)
		return (0.0f);
	if (ratio > 1.0f)
		return (1.0f);
	return (ratio);
}

static int	interpolate_color(int low_color, int high_color, float ratio)
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

static void	put_pixel_to_image(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < fdf->win_width && y >= 0 && y < fdf->win_height)
	{
		dst = fdf->img.addr
			+ (y * fdf->img.line_length + x * (fdf->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	bresenham_draw(t_fdf *fdf, t_point p1, t_point p2, t_line *line)
{
	int		pixel_color;
	float	t;

	t = 0;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		pixel_color = interpolate_color
			(line->color1, line->color2, t / line->steps);
		put_pixel_to_image(fdf, p1.x, p1.y, pixel_color);
		t++;
		line->e2 = 2 * line->err;
		if (line->e2 > -line->dy)
		{
			line->err -= line->dy;
			p1.x += line->sx;
		}
		if (line->e2 < line->dx)
		{
			line->err += line->dx;
			p1.y += line->sy;
		}
	}
}

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
