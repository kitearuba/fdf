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
/* ************************************************************************** */
/*                                                                            */
/*   skip_whitespace                                                          */
/*                                                                            */
/*   Skips over whitespace characters in the input string.                    */
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
/* ************************************************************************** */
static int is_valid_number(const char *str)
{
    int has_digit;

    if (*str == '\0') // If the string starts as empty, it's invalid
        return (0);
    has_digit = 0;
    // Handle strings composed entirely of zeros
    if (*str == '0')
    {
        while (*str == '0')
            str++;
        if (*str == '\0') // If no other characters are found, it's valid
            return (1);
    }
    while (*str)
    {
        if (!ft_isdigit(*str)) // Non-digit character found, invalid
            return (0);
        has_digit = 1; // At least one digit is found
        str++;
    }
    return (has_digit); // Return 1 if we found any valid digits, else 0
}



/* ************************************************************************** */
/*                                                                            */
/*   handle_sign                                                              */
/*                                                                            */
/*   Determines the sign of the number from the input string.                 */
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
/*   handle_error_and_free                                                    */
/*                                                                            */
/*   Frees the 2D array and triggers a fatal error with the given message.    */
/*                                                                            */
/* ************************************************************************** */
static void	handle_error_and_free(char *msg, char **args)
{
	free_2d_array(args);
	fatal_error(msg);
}

/* ************************************************************************** */
/*                                                                            */
/*   parse_strict_atoi                                                        */
/*                                                                            */
/*   Converts a string to an integer while ensuring strict validation.        */
/*   Triggers an error if the input is invalid or exceeds integer limits.     */
/*                                                                            */
/* ************************************************************************** */
int	parse_strict_atoi(const char *str, char **args)
{
	long long	result;
	int			sign;

	result = 0;
	if (!str || !*str)
    	handle_error_and_free("Invalid input detected (empty string)", args);
	skip_whitespace(&str);
    ft_printf("Value before processing: '%s'\n", str); // Debug
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
	if (*str)
		handle_error_and_free("Invalid input detected (extra characters)", args);
	return ((int)(sign * result));
}
