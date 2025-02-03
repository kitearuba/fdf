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
	const int	keys[] = {65307, 65361, 65363, 65362, 65364,
		61, 45, 'q', 'w', 'a', 's', 'p', 't', 'y'};
	int			i;

	i = 0;
	while (i < (int)(sizeof(keys) / sizeof(keys[0])))
	{
		if (key == keys[i])
			return (i);
		i++;
	}
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
