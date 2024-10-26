/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:57:16 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/26 19:47:00 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

/*
This function will apply the projection function to each point of the map.
It will also free the projected lines and replace them with the unprojected
lines.
Finally it will draw the lines.
	// Use 45° for the Cavalier projection, or M_PI / 6 for 30°
	// Apply translation and scaling
	// Perform Cavalier projection
*/
void	cavalier_projection(t_point *point, void *params)
{
	t_map	*map;
	double	angle;

	map = (t_map *)params;
	angle = M_PI / 4;

	point->v.x += map->offset.x;
	point->v.y += map->offset.y;
	point->v.x *= map->scale;
	point->v.y *= map->scale;
	point->v.z *= map->scale;
	point->v.x = point->v.x + point->v.z * cos(angle);
	point->v.y = point->v.y + point->v.z * sin(angle);
}

/*
This function will apply the projection function to each point of the map.
It will also free the projected lines and replace them with the unprojected
lines.
Finally it will draw the lines.
	// Choose a suitable distance for the camera
	// Apply translation and scaling
	 // Avoid division by zero
	// Perform Perspective projection
*/
void	perspective_projection(t_point *point, void *params)
{
	t_map	*map;
	double	distance;

	map = (t_map *)params;
	distance = 1000.0;
	point->v.x += map->offset.x;
	point->v.y += map->offset.y;
	point->v.x *= map->scale;
	point->v.y *= map->scale;
	point->v.z *= map->scale;
	if (point->v.z + distance != 0)
	{
		point->v.x = (point->v.x * distance) / (point->v.z + distance);
		point->v.y = (point->v.y * distance) / (point->v.z + distance);
	}
}

/*
This function will apply the projection function to each point of the map.
It will also free the projected lines and replace them with the unprojected
lines.
Finally it will draw the lines.
	// Free the projected lines
	// Replace the projected lines with the unprojected lines
*/
void	apply_projection(t_mlx *mlx, t_map *map, void (*projection)(t_point *, void *))
{
	t_list	*line;
	t_list	*tmp;
	t_point	*points;

	tmp = map->unprojected_lines;
	ft_lstclear(&map->lines, free);
	map->lines = NULL;
	while (tmp)
	{
		points = malloc(sizeof(t_point) * map->width);
		if (!points)
			exit_with_error("Failed to allocate memory");
		ft_memcpy(points, tmp->content, sizeof(t_point) * map->width);
		line = ft_lstnew(points);
		if (!map->lines)
			map->lines = line;
		else
			ft_lstadd_front(&map->lines, line);
		tmp = tmp->next;
	}
	for_each_point(map, projection, map);
	draw_lines(mlx, map);
}
