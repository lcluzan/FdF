/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:23 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/21 12:22:24 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

void	clear_win(t_mlx *mlx)
{
	ft_bzero(mlx->data_addr, WIDTH * HEIGHT * (mlx->bpp / 8));
}

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

void	draw(t_map *map)
{
	t_mlx	*mlx;

	mlx = init_mlx(map->name);
	for_each_point(map, isometric_projection, map);
	draw_lines(mlx, map);
	listen_events(mlx, map);
	mlx_loop(mlx->ptr);
}
