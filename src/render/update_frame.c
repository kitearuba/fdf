/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/01 03:20:00 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

static void	update_offset(t_fdf *fdf, int *updated)
{
	const int	offset_keys[] = {1, 2, 3, 4};
	const int	offset_values[] = {-2, 2, -2, 2};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (fdf->key_pressed[offset_keys[i]])
		{
			if (i < 2)
				fdf->offset_x += offset_values[i];
			else
				fdf->offset_y += offset_values[i];
			*updated = 1;
		}
		i++;
	}
}

static void	update_zoom_rotation(t_fdf *fdf, int *updated)
{
	const int	keys[] = {5, 6, 7, 8, 9, 10, 11, 12};
	const float	changes[] = {0.2, -0.2, 1, -1, -1, 1, -1, 1};
	int			i;

	i = 0;
	while (i < 8)
	{
		if (fdf->key_pressed[keys[i]])
		{
			if (i < 2)
				fdf->zoom += changes[i];
			else if (i < 4)
				fdf->rotation_x += changes[i];
			else if (i < 6)
				fdf->rotation_y += changes[i];
			else
				fdf->rotation_z += changes[i];
			*updated = 1;
		}
		i++;
	}
}

static void	update_projection_thickness(t_fdf *fdf, int *updated)
{
	if (fdf->key_pressed[13])
	{
		fdf->projections =  0;
		*updated = 1;
	}
	if (fdf->key_pressed[14])
	{
		fdf->projections = 1;
		*updated = 1;
	}
	if (fdf->key_pressed[15] && fdf->line_thickness < 30)
	{
		fdf->line_thickness += 1;
		*updated = 1;
	}
	if (fdf->key_pressed[16] && fdf->line_thickness > 1)
	{
		fdf->line_thickness -= 1;
		*updated = 1;
	}

}

static void	update_color(t_fdf *fdf, int *updated)
{
	if (fdf->key_pressed[17])
	{
		fdf->low_color = DEFAULT_COLOR;
		fdf->high_color = DEFAULT_COLOR;
		*updated = 1;
	}
	if (fdf->key_pressed[18])
	{
		fdf->color_index = (fdf->color_index + 1) % NUM_COLOR_SCHEMES;
		const int *colors = get_color_scheme(fdf->color_index);
		fdf->low_color = colors[0];
		*updated = 1;
	}
	if (fdf->key_pressed[19])
	{
		fdf->color_index = (fdf->color_index + 1) % NUM_COLOR_SCHEMES;
		const int *colors = get_color_scheme(fdf->color_index);
		fdf->high_color = colors[1];
		*updated = 1;
	}
	if (fdf->key_pressed[20])
	{
		fdf->low_color = ICE_BLUE;
		fdf->high_color = ORANGE;
		*updated = 1;
	}
}

int	update_frame(t_fdf *fdf)
{
	int	updated;

	updated = 0;
	if (fdf->key_pressed[0])
		handle_exit(fdf);
	update_projection_thickness(fdf, &updated);
	update_offset(fdf, &updated);
	update_zoom_rotation(fdf, &updated);
	update_color(fdf, &updated);
	if (updated)
		render_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	return (0);
}
