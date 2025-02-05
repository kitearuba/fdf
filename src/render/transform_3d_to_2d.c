/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_3d_to_2d.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona      +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 04:00:00 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/04 23:30:55 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  APPLY ROTATION X  :::                         */
/*                                                                            */
/*   Function: apply_rotation_x                                               */
/*   Description: Applies rotation along the X-axis to a given point.         */
/*                                                                            */
/*   - Converts the rotation angle to radians.                                */
/*   - Rotates the Y and Z coordinates while keeping X unchanged.             */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rotation settings.    */
/*   @param rot Pointer to the rotation structure storing temporary values.   */
/*   @param p The original point to be rotated.                               */
/*                                                                            */
/* ************************************************************************** */
static void	apply_rotation_x(t_fdf *fdf, t_rotation *rot, t_point p)
{
	rot->rad_x = fdf->rotation_x * (M_PI / 180);
	rot->tmp_y = p.y * cos(rot->rad_x) - p.z * sin(rot->rad_x);
	rot->tmp_z = p.y * sin(rot->rad_x) + p.z * cos(rot->rad_x);
	rot->tmp_x = p.x;
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  APPLY ROTATION Y  :::                         */
/*                                                                            */
/*   Function: apply_rotation_y                                               */
/*   Description: Applies rotation along the Y-axis to a given point.         */
/*                                                                            */
/*   - Converts the rotation angle to radians.                                */
/*   - Rotates the X and Z coordinates while keeping Y unchanged.             */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rotation settings.    */
/*   @param rot Pointer to the rotation structure storing temporary values.   */
/*                                                                            */
/* ************************************************************************** */
static void	apply_rotation_y(t_fdf *fdf, t_rotation *rot)
{
	float	tmp_x;

	rot->rad_y = fdf->rotation_y * (M_PI / 180);
	tmp_x = rot->tmp_x;
	rot->tmp_x = tmp_x * cos(rot->rad_y) + rot->tmp_z * sin(rot->rad_y);
	rot->tmp_z = -tmp_x * sin(rot->rad_y) + rot->tmp_z * cos(rot->rad_y);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  APPLY ROTATION Z  :::                         */
/*                                                                            */
/*   Function: apply_rotation_z                                               */
/*   Description: Applies rotation along the Z-axis to a given point.         */
/*                                                                            */
/*   - Converts the rotation angle to radians.                                */
/*   - Rotates the X and Y coordinates while keeping Z unchanged.             */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing rotation settings.    */
/*   @param rot Pointer to the rotation structure storing temporary values.   */
/*                                                                            */
/* ************************************************************************** */
static void	apply_rotation_z(t_fdf *fdf, t_rotation *rot)
{
	float	tmp_x;
	float	tmp_y;

	rot->rad_z = fdf->rotation_z * (M_PI / 180);
	tmp_x = rot->tmp_x;
	tmp_y = rot->tmp_y;
	rot->final_x = tmp_x * cos(rot->rad_z) - tmp_y * sin(rot->rad_z);
	rot->final_y = tmp_x * sin(rot->rad_z) + tmp_y * cos(rot->rad_z);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  APPLY PARALLEL  :::                           */
/*                                                                            */
/*   Function: apply_parallel                                                 */
/*   Description: Projects a 3D point onto a 2D plane using parallel          */
/*                projection.                                                 */
/*                                                                            */
/*   - Scales the X and Y coordinates based on the zoom factor.               */
/*   - Offsets the projection based on user-defined settings.                 */
/*   - Modifies Y based on the Z height for a pseudo-depth effect.            */
/*   - Assigns color based on the Z value.                                    */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing projection settings.  */
/*   @param x The X coordinate of the original 3D point.                      */
/*   @param y The Y coordinate of the original 3D point.                      */
/*   @param z The Z coordinate of the original 3D point.                      */
/*   @return The transformed 2D point with updated coordinates and color.     */
/*                                                                            */
/* ************************************************************************** */
t_point	apply_parallel(t_fdf *fdf, int x, int y, int z)
{
	t_point	p;

	p.x = (x * fdf->zoom) + fdf->offset_x;
	p.y = (y * fdf->zoom) - (z * fdf->zoom / 10) + fdf->offset_y;
	p.z = z;
	p.color = get_color(fdf, z);
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  APPLY ISOMETRIC  :::                          */
/*                                                                            */
/*   Function: apply_isometric                                                */
/*   Description: Projects a 3D point onto a 2D plane using isometric         */
/*                projection.                                                 */
/*                                                                            */
/*   - Applies rotations along the X, Y, and Z axes.                          */
/*   - Computes the final isometric transformation using an angle of 30°.     */
/*   - Scales and offsets the projected coordinates.                          */
/*   - Assigns color based on the transformed Z value.                        */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure containing projection settings.  */
/*   @param p The original 3D point to be transformed.                        */
/*   @return The transformed 2D point with updated coordinates and color.     */
/*                                                                            */
/* ************************************************************************** */
t_point	apply_isometric(t_fdf *fdf, t_point p)
{
	t_rotation	rot;

	apply_rotation_x(fdf, &rot, p);
	apply_rotation_y(fdf, &rot);
	apply_rotation_z(fdf, &rot);
	p.x = (rot.final_x - rot.final_y)
		* cos(0.523599) * fdf->zoom + fdf->offset_x;
	p.y = (rot.final_x + rot.final_y) * sin(0.523599)
		* fdf->zoom - (rot.tmp_z * fdf->zoom / 10) + fdf->offset_y;
	p.z = rot.tmp_z;
	p.color = get_color(fdf, (int)rot.tmp_z);
	return (p);
}
