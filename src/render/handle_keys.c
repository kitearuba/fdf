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

static int	get_key_index(int key)
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
	if (key == 's')
		return (10);
	if (key == 'p')
		return (11);
        if (key == 't')
                return (12);
        if (key == 'y')
                return (13);
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
