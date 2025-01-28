/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/18 19:28:29 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/fdf.h"
#include <stdio.h> // Use printf for debugging

int main(int argc, char **argv)
{
  t_map map;
  int   i;
  int   j;

  i = 0;
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <filename.fdf>\n", argv[0]);
    return (1);
  }
  if (!parse_map(argv[1], &map))
    return (1);
  fprintf(stderr, "Map height: %d\n", map.height);
  fprintf(stderr, "Map width: %d\n", map.width);

  // Print the map data for debugging
  while (i < map.height)
  {
    j = 0;
    while (j < map.width)
    {
      printf("Debug: Accessing map->data[%d][%d] = %d (address: %p)\n", i, j, map.data[i][j], &map.data[i][j]);
      printf("%d ", map.data[i][j]); // Replace ft_printf with printf
      j++;
    }
    printf("\n");
    i++;
  }
  free_map(&map);
  return (0);
}

/*
# include "../../include/fdf.h"

int main(int argc, char **argv)
{
  t_map map;
  int   i;
  int   j;

  i = 0;
  if (argc != 2)
  {
    ft_printf_fd(STDERR, "Usage: %s <filename.fdf>\n", argv[0]);
    return (1);
  }
  if (!parse_map(argv[1], &map))
    return (1);
  ft_printf_fd(STDERR, "Map height: %d\n", map.height);
  ft_printf_fd(STDERR, "Map width: %d\n", map.width);

  // Print the map data for debugging
  while (i < map.height)
  {
    j = 0;
    while (j < map.width)
    {
      ft_printf_fd(STDERR, "Debug: Accessing map->data[%d][%d] = %d (address: %p)\n",
                   i, j, map.data[i][j], &map.data[i][j]);
      ft_printf("%d ", map.data[i][j]);
      j++;
    }
    ft_printf("\n");
    i++;
  }
  free_map(&map);
  return (0);
}
 */