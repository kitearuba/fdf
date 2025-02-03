/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_thick_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:45:25 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/02 23:37:10 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

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
