/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_min_max_z.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 23:14:36 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	find_min_max_z(t_fdf *fdf)
{
	int	y;
	int	x;

	y = 0;
	fdf->min_z = MAX_INT;
	fdf->max_z = MIN_INT;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			int z = fdf->map->data[y][x];
			if (z < fdf->min_z)
				fdf->min_z = z;
			if (z > fdf->max_z)
				fdf->max_z = z;
			x++;
		}
		y++;
	}
}
