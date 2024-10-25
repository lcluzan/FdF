/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:23 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/25 15:51:51 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
This function will remove all the pixels on the screen but replacing all
the screen data with zeros.
*/
void	clear_win(t_mlx *mlx)
{
	ft_bzero(mlx->data_addr, WIDTH * HEIGHT * (mlx->bpp / 8));
}

/*
This function takes a point and will multiply 2 matrix to its coords.
A 45º (π/4 rad) rotation on the z axis.
And -arctan(sqrt(2)) on the x axis.

This way we go from a top view to an isometric view.

It will also translate the view to the center of the screen using the map offset
 value. And zoom in but multiplying
coords by the map scale value.
*/
void	isometric_projection(t_point *point, void *params)
{
	t_map	*map;

	map = (t_map *)params;
	point->v.x += map->offset.x;
	point->v.y += map->offset.y;
	point->v.x *= map->scale;
	point->v.y *= map->scale;
	point->v.z *= map->scale;
	point->v = multiply_vector_by_matrix(
			point->v,
			get_rotation_matrix(M_PI / 4, 'z')
			);
	point->v = multiply_vector_by_matrix(
			point->v,
			get_rotation_matrix(-atan(sqrt(2)), 'x')
			);
}

void	draw_map_line(t_mlx *mlx, t_map *map, t_list *map_line, size_t col)
{
	t_point	p1;
	t_point	p2;

	p1 = round_point(((t_point *)map_line->content)[col]);
	if (col < map->width - 1)
	{
		p2 = round_point(((t_point *)map_line->content)[col + 1]);
		draw_line(mlx, p1, p2);
	}
	if (map_line->next)
	{
		p2 = round_point(((t_point *)map_line->next->content)[col]);
		draw_line(mlx, p1, p2);
	}
}

/*
This function will first clean the screen.

Then loop through every points of the map and for each point, it will draw
a line between the (x;y) coords
of the points and the (x;y) coords of the point on the right (if it exists)
and the one just below (if it exists too).
clear mlx window
loop through points
We round the points cause' the coords are store in a float and our bresenham
implementation doesn't work with decimals.
draw horizontal line by connecting with the point on the right
draw vertical line by connecting with the point below
push the new version of the screen to make it appear on the screen
*/

void	draw_lines(t_mlx *mlx, t_map *map)
{
	size_t	i;
	t_list	*map_line;

	clear_win(mlx);
	map_line = map->lines;
	while (map_line)
	{
		i = 0;
		while (i < map->width)
		{
			draw_map_line(mlx, map, map_line, i);
			++i;
		}
		map_line = map_line->next;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
}

/*
  This function:

- initiate the mlx
- apply an isometric projection on the map coordinates
- draw the map on the screen
- subscribe to mlx events
- run the mlx loop (so the program doesn't just stop once the screen
has been drawn)
*/
void	draw(t_map *map)
{
	t_mlx	*mlx;

	mlx = init_mlx(map->name);
	for_each_point(map, isometric_projection, map);
	draw_lines(mlx, map);
	listen_events(mlx, map);
	mlx_loop(mlx->ptr);
}
