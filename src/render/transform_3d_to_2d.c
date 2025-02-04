/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_3d_to_2d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona      +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 04:00:00 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/02 02:15:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	apply_rotation_x(t_fdf *fdf, t_rotation *rot, int x, int y, int z)
{
	rot->rad_x = fdf->rotation_x * (M_PI / 180);
	rot->tmp_y = y * cos(rot->rad_x) - z * sin(rot->rad_x);
	rot->tmp_z = y * sin(rot->rad_x) + z * cos(rot->rad_x);
	rot->tmp_x = x; // X remains unchanged in X-axis rotation
}

static void	apply_rotation_y(t_fdf *fdf, t_rotation *rot)
{
	rot->rad_y = fdf->rotation_y * (M_PI / 180);
	float tmp_x = rot->tmp_x;
	rot->tmp_x = tmp_x * cos(rot->rad_y) + rot->tmp_z * sin(rot->rad_y);
	rot->tmp_z = -tmp_x * sin(rot->rad_y) + rot->tmp_z * cos(rot->rad_y);
}

static void	apply_rotation_z(t_fdf *fdf, t_rotation *rot)
{
	rot->rad_z = fdf->rotation_z * (M_PI / 180);
	float tmp_x = rot->tmp_x;
	float tmp_y = rot->tmp_y;
	rot->final_x = tmp_x * cos(rot->rad_z) - tmp_y * sin(rot->rad_z);
	rot->final_y = tmp_x * sin(rot->rad_z) + tmp_y * cos(rot->rad_z);
}

t_point	apply_parallel(t_fdf *fdf, int x, int y, int z)
{
	t_point	p;

	p.x = (x * fdf->zoom) + fdf->offset_x;
	p.y = (y * fdf->zoom) - (z * fdf->zoom / 10) + fdf->offset_y;
	p.z = z;
	p.color = get_color(fdf, z);
	return (p);
}

t_point	apply_isometric(t_fdf *fdf, int x, int y, int z)
{
	t_point		p;
	t_rotation	rot;


	apply_rotation_x(fdf, &rot, x, y, z);
	apply_rotation_y(fdf, &rot);
	apply_rotation_z(fdf, &rot);
	p.x = (rot.final_x - rot.final_y) * cos(0.523599) * fdf->zoom + fdf->offset_x;
	p.y = (rot.final_x + rot.final_y) * sin(0.523599) * fdf->zoom - (rot.tmp_z * fdf->zoom / 10)
		+ fdf->offset_y;
	p.z = rot.tmp_z;
	p.color = get_color(fdf,  (int)rot.tmp_z);
	return (p);
}
