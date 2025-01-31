/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:48:40 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	get_key_index(int key)
{
	if (key == 65307)
		return (0);
	if (key == 65361)
		return (1);
	if (key == 65363)
		return (2);
	if (key == 65362)
		return (3);
	if (key == 65364)
		return (4);
	if (key == 61)
		return (5);
	if (key == 45)
		return (6);
	if (key == 'q')
		return (7);
	if (key == 'w')
		return (8);
	if (key == 'a')
		return (9);
	if (key == 'd')
		return (10);
	return (-1);
}

int	handle_key_press(int key, t_fdf *fdf)
{
	int	index;

	index = get_key_index(key);
	if (index >= 0 && index < KEY_COUNT)
		fdf->key_pressed[index] = 1;
	return (0);
}

int	handle_key_release(int key, t_fdf *fdf)
{
	int	index;

	index = get_key_index(key);
	if (index >= 0 && index < KEY_COUNT)
		fdf->key_pressed[index] = 0;
	return (0);
}

int	update_frame(t_fdf *fdf)
{
	int	updated;

	updated = 0;
	if (fdf->key_pressed[0])
		handle_exit(fdf);
	if (fdf->key_pressed[1])
	{
		fdf->offset_x -= 2;
		updated = 1;
	}
	if (fdf->key_pressed[2])
	{
		fdf->offset_x += 2;
		updated = 1;
	}
	if (fdf->key_pressed[3])
	{
		fdf->offset_y -= 2;
		updated = 1;
	}
	if (fdf->key_pressed[4])
	{
		fdf->offset_y += 2;
		updated = 1;
	}
	if (fdf->key_pressed[5])
	{
		fdf->zoom += 0.2;
		updated = 1;
	}
	if (fdf->key_pressed[6])
	{
		fdf->zoom -= 0.2;
		updated = 1;
	}
	if (fdf->key_pressed[7])
	{
		fdf->rotation_x += 1;
		updated = 1;
	}
	if (fdf->key_pressed[8])
	{
		fdf->rotation_x -= 1;
		updated = 1;
	}
	if (fdf->key_pressed[9])
	{
		fdf->rotation_y -= 1;
		updated = 1;
	}
	if (fdf->key_pressed[10])
	{
		fdf->rotation_y += 1;
		updated = 1;
	}
	if (updated)
		render_fdf(fdf);
	return (0);
}
