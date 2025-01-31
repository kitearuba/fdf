/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2024/12/28 23:00:05 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"


void	free_fdf(t_fdf *fdf)
{
  if (fdf)
  {
    if (fdf->map)
      free_map(fdf->map);
    if (fdf->img.img)
      mlx_destroy_image(fdf->mlx, fdf->img.img);
    if (fdf->win)
    {
      mlx_destroy_window(fdf->mlx, fdf->win);
      fdf->win = NULL;
    }
    if (fdf->mlx)
    {
      mlx_destroy_display(fdf->mlx);
      free(fdf->mlx);
      fdf->mlx = NULL;
    }
    free(fdf);
  }
}