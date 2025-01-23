
#ifndef FDF_FDF_H
#define FDF_FDF_H

/* ************************************************************************** */
/*                               Includes                                     */
/* ************************************************************************** */

# include <unistd.h>
# include <fcntl.h> // For open()
# include <stdlib.h> // For exit() and abs()
# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"

/* ************************************************************************** */
/*                                  Macros                                    */
/* ************************************************************************** */

# define STDERR 2
# define ESC_KEY 65307 // Keycode for the ESC key on Linux
# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct s_map
{
    int **grid;      // 2D array to hold z-values
    int width;       // Number of columns
    int height;      // Number of rows
} t_map;

typedef struct s_fdf {
    void *mlx;
    void *win;
    t_map *map;
    int zoom;
    double angle;
} t_fdf;


/* ************************************************************************** */
/*                           Function Prototypes                              */
/* ************************************************************************** */
t_map   *parse_map(const char *filename);
void    free_2d_array(char **arr);
int     parse_strict_atoi(const char *str, char **args);
void	fatal_error(const char *msg);


#endif //FDF_FDF_H
