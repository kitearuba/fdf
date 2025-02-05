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

/* ************************************************************************** */
/*                                                                            */
/*                         :::  PUT PIXEL TO IMAGE  :::                       */
/*                                                                            */
/*   Function: put_pixel_to_image                                             */
/*   Description: Draws a pixel with a specified color on the image buffer.   */
/*                                                                            */
/*   - Ensures the pixel coordinates are within the window bounds.            */
/*   - Calculates the correct memory position in the image buffer.            */
/*   - Stores the color value at the computed address.                        */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing the image buffer.     */
/*   @param x The x-coordinate of the pixel.                                  */
/*   @param y The y-coordinate of the pixel.                                  */
/*   @param color The color to set for the pixel.                             */
/*                                                                            */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*                                                                            */
/*                         :::  BRESENHAM DRAW  :::                           */
/*                                                                            */
/*   Function: bresenham_draw                                                 */
/*   Description: Implements the Bresenham algorithm for drawing lines.       */
/*                                                                            */
/*   - Uses integer-based calculations for efficient line drawing.            */
/*   - Computes and assigns pixel colors based on interpolation.              */
/*   - Determines pixel placement by updating error terms.                    */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure.                                 */
/*   @param p1 The starting point of the line.                                */
/*   @param p2 The ending point of the line.                                  */
/*   @param line Pointer to the structure containing line attributes.         */
/*                                                                            */
/* ************************************************************************** */
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
