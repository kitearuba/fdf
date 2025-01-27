/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_counter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:51:02 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/27 17:51:21 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int ft_word_counter(char const *str, char c)
{
  int i;
  int words;

  words = 0;
  i = 0;
  while (str[i])
  {
    while (str[i] == c && str[i] != '\0')
      i++;
    if (str[i])
      words++;
    while (str[i] != c && str[i] != '\0')
      i++;
  }
  return (words);
}
