/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_strict_atoi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:07:41 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/18 12:28:01 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   skip_whitespace                                                          */
/*                                                                            */
/*   Skips over whitespace characters in the input string.                    */
/*                                                                            */
/*   @param str: Pointer to the input string.                                 */
/*                                                                            */
/* ************************************************************************** */
static void	skip_whitespace(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n'
		|| **str == '\f' || **str == '\v' || **str == '\r')
		(*str)++;
}

/* ************************************************************************** */
/*                                                                            */
/*   is_valid_number                                                          */
/*                                                                            */
/*   Validates the input string to ensure it represents a valid number.       */
/*                                                                            */
/*   @param str: Pointer to the input string.                                 */
/*   @return: 1 if valid, 0 otherwise.                                        */
/*                                                                            */
/* ************************************************************************** */
static int	is_valid_number(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*   handle_error_and_free                                                    */
/*                                                                            */
/*   Handles error by freeing resources and triggering an error handler.      */
/*                                                                            */
/*   @param stack: The stack structure to clean up.                           */
/*   @param args: The 2D array to free.                                       */
/*                                                                            */
/* ************************************************************************** */
static void	handle_error_and_free(t_stack *stack, char **args)
{
	free_2d_array(args);
	handle_error(stack, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*   handle_sign                                                              */
/*                                                                            */
/*   Determines the sign of the number from the input string.                 */
/*                                                                            */
/*   @param str: Pointer to the input string.                                 */
/*   @return: -1 if the number is negative, 1 otherwise.                      */
/*                                                                            */
/* ************************************************************************** */
static int	handle_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

/* ************************************************************************** */
/*                                                                            */
/*   parse_strict_atoi                                                        */
/*                                                                            */
/*   Converts a string to an integer while ensuring strict validation.        */
/*   Triggers an error if the input is invalid or exceeds integer limits.     */
/*                                                                            */
/*   @param str: The input string to parse.                                   */
/*   @return: The converted integer value.                                    */
/*                                                                            */
/* ************************************************************************** */
int	parse_strict_atoi(const char *str, t_stack **stack, char **args)
{
	long long	result;
	int			sign;

	result = 0;
	skip_whitespace(&str);
	if (!is_valid_number(str))
		handle_error_and_free(*stack, args);
	sign = handle_sign(&str);
	while (*str == 0)
		str++;
	if (!*str)
		fatal_error();
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if ((sign * result) > MAX_INT || (sign * result) < MIN_INT)
			handle_error_and_free(*stack, args);
		str++;
	}
	if (*str)
		fatal_error();
	return ((int)(sign * result));
}
