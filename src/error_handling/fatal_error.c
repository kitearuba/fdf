/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:29:05 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 21:53:20 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*   fatal_error                                                              */
/*                                                                            */
/*   Prints an error message to STDERR and exits the program.                 */
/*   This function is used to terminate execution on critical errors.         */
/*                                                                            */
/* ************************************************************************** */

void	fatal_error(const char *msg)
{
	if (msg)
		ft_printf_fd(STDERR, "%s", msg);
	ft_printf_fd(STDERR, "\n");
	exit(EXIT_FAILURE);
}
