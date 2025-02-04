/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:45:25 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/02 23:37:10 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
/*
static int	interpolate_color(int start_color, int end_color, float t)
{
	int	r;
	int	g;
	int	b;

	r = ((start_color >> 16) & 0xFF) * (1 - t)
		+ ((end_color >> 16) & 0xFF) * t;
	g = ((start_color >> 8) & 0xFF) * (1 - t)
		+ ((end_color >> 8) & 0xFF) * t;
	b = (start_color & 0xFF) * (1 - t) + (end_color & 0xFF) * t;
	return ((r << 16) | (g << 8) | b);
}
*/
static float clamp_ratio(float ratio)
{
	if (ratio < 0.0f)
		return (0.0f);
	if (ratio > 1.0f)
		return (1.0f);
	return (ratio);
}

static int	interpolate_color(int low_color, int high_color, float ratio)
{
	int	red, green, blue;

	ratio = clamp_ratio(ratio);
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

static void	init_line_struct(t_line *line, t_point p1, t_point p2, t_fdf *fdf)
{
	line->dx = abs(p2.x - p1.x);
	line->dy = abs(p2.y - p1.y);
	line->sx = -1;
	line->sy = -1;
	if (p1.x < p2.x)
		line->sx = 1;
	if (p1.y < p2.y)
		line->sy = 1;
	line->err = line->dx - line->dy;
	line->color1 = get_color(fdf, p1.z);
	line->color2 = get_color(fdf, p2.z);
	line->steps = line->dx;
	if (line->dy > line->dx)
		line->steps = line->dy;
}

static void	bresenham_draw(t_fdf *fdf, t_point p1, t_point p2, t_line *line)
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

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_line	line;

	init_line_struct(&line, p1, p2, fdf);
	bresenham_draw(fdf, p1, p2, &line);
}
