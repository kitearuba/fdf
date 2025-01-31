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
	int	i;
	int	j;

	i = 0;
	j = 0;
	fdf->min_z = fdf->map->data[0][0];
	fdf->max_z = fdf->map->data[0][0];
	while (i < fdf->map->height)
	{
		while (j < fdf->map->width)
		{
			if (fdf->map->data[i][j] < fdf->min_z)
				fdf->min_z = fdf->map->data[i][j];
			if (fdf->map->data[i][j] > fdf->max_z)
				fdf->max_z = fdf->map->data[i][j];
			j++;
		}
		i++;
	}
}

/*
void find_min_max_z(t_fdf *fdf)
{
  int x, y;

  fdf->min_z = fdf->map->data[0][0];
  fdf->max_z = fdf->map->data[0][0];

  y = 0;
  while (y < fdf->map->height)
  {
    x = 0;
    while (x < fdf->map->width)
    {
      if (fdf->map->data[y][x] < fdf->min_z)
        fdf->min_z = fdf->map->data[y][x];
      if (fdf->map->data[y][x] > fdf->max_z)
        fdf->max_z = fdf->map->data[y][x];
      x++;
    }
    y++;
  }
}
*/
