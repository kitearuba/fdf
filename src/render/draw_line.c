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

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_line	line;

	init_line_struct(&line, p1, p2, fdf);
	bresenham_draw(fdf, p1, p2, &line);
}

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
