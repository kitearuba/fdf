/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/18 19:28:29 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int get_key_index(int key)
{
  if (key == 65307) return (0);  // ESC
  if (key == 65361) return (1);  // Left Arrow
  if (key == 65363) return (2);  // Right Arrow
  if (key == 65362) return (3);  // Up Arrow
  if (key == 65364) return (4);  // Down Arrow
  if (key == 61) return (5);     // `+`
  if (key == 45) return (6);
  if (key == 'q') return (7);
  if (key == 'w') return (8);
  if (key == 'a') return (9);
  if (key == 'd') return (10);
  return (-1); // Ignore unknown keys
}

int handle_key_press(int key, t_fdf *fdf)
{
  int index = get_key_index(key);
  if (index >= 0 && index < KEY_COUNT)
    fdf->key_pressed[index] = 1;
  return (0);
}

int handle_key_release(int key, t_fdf *fdf)
{
  int index = get_key_index(key);
  if (index >= 0  && index < KEY_COUNT)
    fdf->key_pressed[index] = 0;
  return (0);
}

int update_frame(t_fdf *fdf)
{
  int updated; // Track if movement happened

  if (fdf->key_pressed[0]) // Left arrow
    handle_exit(fdf);
  updated = 0;
  if (fdf->key_pressed[1]) // Left arrow
  {
    fdf->offset_x -= 2;
    updated = 1;
  }
  if (fdf->key_pressed[2]) // Right arrow
  {
    fdf->offset_x += 2;
    updated = 1;
  }
  if (fdf->key_pressed[3]) // Up arrow
  {
    fdf->offset_y -= 2;
    updated = 1;
  }
  if (fdf->key_pressed[4]) // Down arrow
  {
    fdf->offset_y += 2;
    updated = 1;
  }
  if (fdf->key_pressed[5]) // `+` key (Zoom in)
  {
    fdf->zoom += 0.2;
    updated = 1;
  }
  if (fdf->key_pressed[6]) // `-` key (Zoom out)
  {
    fdf->zoom -= 0.2;
    updated = 1;
  }
  if (fdf->key_pressed[7])  // Rotate X-axis (Up)
  {
    fdf->rotation_x += 1;
    updated = 1;
  }
  if (fdf->key_pressed[8])  // Rotate X-axis (Down)
  {
    fdf->rotation_x -= 1;
    updated = 1;
  }
  if (fdf->key_pressed[9])  // Rotate Y-axis (Left)
  {
    fdf->rotation_y -= 1;
    updated = 1;
  }
  if (fdf->key_pressed[10])  // Rotate Y-axis (Right)
  {
    fdf->rotation_y += 1;
    updated = 1;
  }
  if (updated) // Only re-render if something changed
    render_fdf(fdf);
  return (0);
}
