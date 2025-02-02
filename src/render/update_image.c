/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/01 03:20:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	update_movement(t_fdf *fdf, int *updated)
{
  if (fdf->key_pressed[1])
  {
    fdf->offset_x -= 2;
    *updated = 1;
  }
  if (fdf->key_pressed[2])
  {
    fdf->offset_x += 2;
    *updated = 1;
  }
  if (fdf->key_pressed[3])
  {
    fdf->offset_y -= 2;
    *updated = 1;
  }
  if (fdf->key_pressed[4])
  {
    fdf->offset_y += 2;
    *updated = 1;
  }
}

static void	update_zoom(t_fdf *fdf, int *updated)
{
  if (fdf->key_pressed[5])
  {
    fdf->zoom += 0.2;
    *updated = 1;
  }
  if (fdf->key_pressed[6])
  {
    fdf->zoom -= 0.2;
    *updated = 1;
  }
}

static void	update_rotation(t_fdf *fdf, int *updated)
{
  if (fdf->key_pressed[7])
  {
    fdf->rotation_x += 1;
    *updated = 1;
  }
  if (fdf->key_pressed[8])
  {
    fdf->rotation_x -= 1;
    *updated = 1;
  }
  if (fdf->key_pressed[9])
  {
    fdf->rotation_y -= 1;
    *updated = 1;
  }
  if (fdf->key_pressed[10])
  {
    fdf->rotation_y += 1;
    *updated = 1;
  }
}

static void	update_projection_or_thickness(t_fdf *fdf, int *updated)
{
  if (fdf->key_pressed[11])
  {
    if (fdf->projections == 0)
      fdf->projections = 1;
    else
      fdf->projections = 0;
    *updated = 1;
  }
  if (fdf->key_pressed[12])
  {
    if (fdf->line_thickness < 30)
      fdf->line_thickness += 1;
    *updated = 1;
  }
  if (fdf->key_pressed[13])
  {
    if (fdf->line_thickness > 1)
      fdf->line_thickness -= 1;
    *updated = 1;
  }
}

int	update_frame(t_fdf *fdf)
{
  int	updated;

  updated = 0;
  if (fdf->key_pressed[0])
    handle_exit(fdf);
  update_projection_or_thickness(fdf, &updated);
  update_movement(fdf, &updated);
  update_zoom(fdf, &updated);
  update_rotation(fdf, &updated);
  if (updated)
    render_fdf(fdf);
  return (0);
}
