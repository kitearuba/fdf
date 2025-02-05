/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:45:25 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/04 20:47:49 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  INIT LINE STRUCT  :::                         */
/*                                                                            */
/*   Function: init_line_struct                                               */
/*   Description: Initializes a t_line structure with line properties.        */
/*                                                                            */
/*   - Calculates the differences (dx, dy) between the two points.            */
/*   - Determines the step direction for X and Y movement.                    */
/*   - Initializes the Bresenham error term.                                   */
/*   - Assigns interpolated colors based on Z-values.                         */
/*   - Computes the number of steps required for line interpolation.          */
/*                                                                            */
/*   @param line Pointer to the line structure to initialize.                 */
/*   @param p1 The starting point of the line.                                */
/*   @param p2 The ending point of the line.                                  */
/*   @param fdf Pointer to the FDF structure for color calculations.          */
/*                                                                            */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*                                                                            */
/*                         :::  DRAW LINE  :::                                */
/*                                                                            */
/*   Function: draw_line                                                      */
/*   Description: Draws a basic line using the Bresenham algorithm.           */
/*                                                                            */
/*   - Calls init_line_struct to initialize line properties.                  */
/*   - Uses bresenham_draw to render the line pixel by pixel.                 */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rendering data.       */
/*   @param p1 The starting point of the line.                                */
/*   @param p2 The ending point of the line.                                  */
/*                                                                            */
/* ************************************************************************** */
void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_line	line;

	init_line_struct(&line, p1, p2, fdf);
	bresenham_draw(fdf, p1, p2, &line);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  DRAW THICK LINE  :::                          */
/*                                                                            */
/*   Function: draw_thick_line                                                */
/*   Description: Draws a thicker line by offsetting parallel lines.          */
/*                                                                            */
/*   - Iterates through offset positions based on line thickness.             */
/*   - Determines whether to shift X or Y based on the line's direction.      */
/*   - Calls draw_line multiple times to create a thickness effect.           */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rendering data.       */
/*   @param p1 The starting point of the thick line.                          */
/*   @param p2 The ending point of the thick line.                            */
/*                                                                            */
/* ************************************************************************** */
void	draw_thick_line(t_fdf *fdf, t_point p1, t_point p2)
{
	int		offset;
	t_point	new_p1;
	t_point	new_p2;

	offset = -fdf->line_thickness / 10;
	while (offset <= fdf->line_thickness / 10)
	{
		new_p1 = p1;
		new_p2 = p2;
		if (abs(p2.x - p1.x) > abs(p2.y - p1.y))
		{
			new_p1.y += offset;
			new_p2.y += offset;
		}
		else
		{
			new_p1.x += offset;
			new_p2.x += offset;
		}
		draw_line(fdf, new_p1, new_p2);
		offset++;
	}
}
