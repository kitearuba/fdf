/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_height_counter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:51:39 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/27 17:51:41 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int ft_line_counter(int fd)
{
  char	*buffer;
  int   height;
  size_t   bytes_read;
  int   i;

  height = 0;
  ft_printf("height: %d\n", height);
  buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
  if (!buffer)
    return (-1);
  bytes_read = read(fd, buffer, BUFFER_SIZE);
  while (bytes_read > 0)
  {
    buffer[bytes_read] = '\0';
    i = 0;
    ft_printf("check while 1\n");
    while (buffer[i])
    {
      ft_printf("check while 2\n");
      ft_printf("buffer: %c\n", buffer[i]);
      if (buffer[i] == '\n' || buffer[i] == '\0')
      {
        ft_printf("check if\n");
        height++;
        ft_printf("height: %d\n", height);
      }
      i++;
    }
    bytes_read = read(fd, buffer, BUFFER_SIZE);
  }
  ft_printf("check exit while\n");
  free(buffer);
  return (height);
}