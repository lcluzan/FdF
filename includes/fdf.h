#ifndef FDF_H
#define FDF_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define WIDTH 1320
# define HEIGHT 720
# define MARGIN 120
#define M_PI 3.14159265358979323846

# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_CLICK_MIDDLE 3

# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6

# define MOUSE_SENSITIVITY 80

typedef struct s_options {
  char *map_path;
} t_options;

typedef struct s_color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} t_color;

typedef struct s_vec {
  double x;
  double y;
  double z;
} t_vec;

typedef struct s_map {
  t_list *lines;
  size_t width;
  size_t height;
  double scale;
  t_vec offset;
  char *name;
} t_map;

typedef struct s_mlx {
  void *ptr;
  void *win;
  void *img;
  char *data_addr;
  int bpp;
  int size_line;
  int endian;
} t_mlx;

typedef struct s_point {
  t_vec v;
  t_color color;
} t_point;

// matrix

typedef struct s_matrix {
  t_vec i;
  t_vec j;
  t_vec k;
} t_matrix;

// controls

typedef struct s_mouse {
  t_vec position;
  bool is_down;
} t_mouse;

typedef struct s_controls {
  t_mouse mouse;
  t_map *map;
  t_mlx *mlx;
} t_controls;

#define WHITE ((t_color){ 0xff, 0xff, 0xff })

// parser
t_map *parse_map(char *map_path);

// utils
void exit_with_error(const char *message);
bool is_hex_alpha(int c);
void for_each_point(t_map *map, void (*fn)(t_point *point, void *params), void *params);
t_point round_point(t_point p);
int open_map(char *map_path);

// math_utils
int32_t abs(int32_t n);
int32_t min(int32_t a, int32_t b);
int32_t max(int32_t a, int32_t b);
int32_t diff(int32_t a, int32_t b);

// parser_utils
bool parse_height(char *str, double *height);
bool parse_color(char *str, t_color *color);

// map
t_map *new_map();
void free_map(t_map *map);

// draw
void  draw(t_map *map);
void draw_lines(t_mlx *mlx, t_map *map);

// controls
t_controls *listen_events(t_mlx *mlx, t_map *map);

// bresenham
void draw_line(t_mlx *mlx, t_point a, t_point b);

// matrix
void apply_matrix(t_point *point, void *params);
t_matrix	multiply_matrix_by_matrix(t_matrix m1, t_matrix m2);
t_matrix get_rotation_matrix(double rad, char axis);
t_vec	multiply_vector_by_matrix(t_vec v, t_matrix m);

// mlx
t_mlx *init_mlx(const char *name);

#endif
