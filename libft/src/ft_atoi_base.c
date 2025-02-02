/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:32:43 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/02 22:55:33 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	get_digit_value(char c, int base)
{
  int	value;

  value = -1;
  if (c >= '0' && c <= '9')
    value = c - '0';
  else if (c >= 'A' && c <= 'F')
    value = c - 'A' + 10;
  else if (c >= 'a' && c <= 'f')
    value = c - 'a' + 10;
  if (value >= base)
    value = -1;
  return (value);
}

int	ft_atoi_base(const char *str, int base)
{
  long	result;
  int		sign;
  int		value;

  if (!str || base < 2 || base > 16)
    return (0);
  sign = 1;
  while (*str == ' ' || *str == '\t' || *str == '\n'
         || *str == '\v' || *str == '\f' || *str == '\r')
    str++;
  if (*str == '-' || *str == '+')
  {
    if (*str == '-')
      sign = -1;
    str++;
  }
  if (base == 16 && *str == '0' && (str[1] == 'x' || str[1] == 'X'))
    str += 2;
  result = 0;
  while (*str)
  {
    value = get_digit_value(*str, base);
    if (value == -1)
      break;
    if (result > (MAX_LONG - value) / base)
    {
      if (sign == 1)
        return (MAX_INT);
      return (MIN_INT);
    }
    result = result * base + value;
    str++;
  }
  return ((int)(result * sign));
}
