/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:45:25 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/01 04:24:25 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

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

static void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
  t_line	line;

  line.dx = abs(p2.x - p1.x);
  line.dy = abs(p2.y - p1.y);
  if (p1.x < p2.x)
    line.sx = 1;
  else
    line.sx = -1;
  if (p1.y < p2.y)
    line.sy = 1;
  else
    line.sy = -1;
  line.err = line.dx - line.dy;
  line.color1 = get_color(p1.z, fdf->min_z, fdf->max_z);
  line.color2 = get_color(p2.z, fdf->min_z, fdf->max_z);
  while (p1.x != p2.x || p1.y != p2.y)
  {
    put_pixel_to_image(fdf, p1.x, p1.y, line.color1);
    put_pixel_to_image(fdf, p2.x, p2.y, line.color2);
    line.e2 = 2 * line.err;
    if (line.e2 > -line.dy)
    {
      line.err -= line.dy;
      p1.x += line.sx;
    }
    if (line.e2 < line.dx)
    {
      line.err += line.dx;
      p1.y += line.sy;
    }
  }
}

void	draw_thick_line(t_fdf *fdf, t_point p1, t_point p2, int thickness)
{
  int		offset;
  t_point	new_p1;
  t_point	new_p2;

  offset = -thickness / 2;
  while (offset <= thickness / 2)
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