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

#include "../../include/fdf.h"

static void skip_whitespace(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n' ||
	       **str == '\f' || **str == '\v' || **str == '\r')
		(*str)++;
}

static int is_valid_number(const char *str)
{
	if (!str || *str == '\0') // Empty string is invalid
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str)) // Non-digit character makes it invalid
			return (0);
		str++;
	}
	return (1);
}

static int handle_sign(const char **str)
{
	int sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static void handle_error_and_free(char *msg, char **args)
{
	free_2d_array(args);
	fatal_error(msg);
}

int parse_strict_atoi(const char *str, char **args)
{
	long long result;
	int sign;

	result = 0;
	if (!str || !*str)
		handle_error_and_free("Invalid input detected (empty string)", args);
	skip_whitespace(&str);
	sign = handle_sign(&str);
	if (!is_valid_number(str))
		handle_error_and_free("Invalid input detected (invalid number)", args);
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if ((sign * result) > MAX_INT || (sign * result) < MIN_INT)
			handle_error_and_free("Invalid input detected (out of range)", args);
		str++;
	}
	return ((int)(sign * result));
}
