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

/* ************************************************************************** */
/*                                                                            */
/*                         :::  GET KEY INDEX  :::                            */
/*                                                                            */
/*   Function: get_key_index                                                  */
/*   Description: Retrieves the index of a key from a predefined key list.    */
/*                                                                            */
/*   - Compares the given key against an array of recognized key codes.       */
/*   - Returns the index of the key if found, or -1 if the key is unrecognized.*/
/*                                                                            */
/*   @param key The keycode to search for.                                    */
/*   @return The index of the key in the list, or -1 if not found.            */
/*                                                                            */
/* ************************************************************************** */
static int	get_key_index(int key)
{
	const int	keys[] = {65307, 65361, 65363, 65362, 65364, 61, 45,
		'q', 'w', 'a', 's', 'z', 'x', 'p', 'o', 't', 'y', '5', '6', '7',
		'8'};
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

/* ************************************************************************** */
/*                                                                            */
/*                         :::  HANDLE KEY PRESS  :::                         */
/*                                                                            */
/*   Function: handle_key_press                                               */
/*   Description: Marks a key as pressed in the FDF key tracking array.       */
/*                                                                            */
/*   - Retrieves the index of the pressed key using get_key_index.            */
/*   - If the key is found, sets its corresponding entry in fdf->key_pressed. */
/*                                                                            */
/*   @param key The keycode of the pressed key.                               */
/*   @param fdf Pointer to the FDF structure managing key states.             */
/*   @return Always returns 0 (can be modified for event handling).           */
/*                                                                            */
/* ************************************************************************** */
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
