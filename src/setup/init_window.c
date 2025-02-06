/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/05 21:55:44 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  SET WINDOW SIZE  :::                          */
/*                                                                            */
/*   Function: set_window_size                                                */
/*   Description: Defines the default window dimensions for rendering.        */
/*                                                                            */
/*   - Sets the window width to MACRO WIN_WIDTH.                              */
/*   - Sets the window height to MACRO WIN_HEIGHT.                            */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure where window size is stored.     */
/*                                                                            */
/* ************************************************************************** */
void	set_window_size(t_fdf *fdf)
{
	fdf->win_width = WIN_WIDTH;
	fdf->win_height = WIN_HEIGHT;
}
