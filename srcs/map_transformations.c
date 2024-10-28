/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_transformations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:29:17 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/28 16:30:14 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_vec(t_point *point, void *params)
{
	t_vec	vec;

	vec = *(t_vec *)params;
	point->v.x += vec.x;
	point->v.y += vec.y;
	point->v.z += vec.z;
}

void	translate_map(int button, t_mlx *mlx, t_map *map)
{
	t_vec	vec;
	double	shift;

	shift = KEY_SENSITIVITY * 0.1;
	if (button == KEY_LEFT)
		vec = (t_vec){-shift, 0, 0};
	else if (button == KEY_UP)
		vec = (t_vec){0, shift, 0};
	else if (button == KEY_RIGHT)
		vec = (t_vec){shift, 0, 0};
	else if (button == KEY_DOWN)
		vec = (t_vec){0, -shift, 0};
	else
		return ;
	for_each_point(map, add_vec, &vec);
	draw_lines(mlx, map);
}

void	scale_map(int button, t_mlx *mlx, t_map *map)
{
	t_matrix	matrix;
	double		scale_factor;

	scale_factor = KEY_SENSITIVITY * 0.002;
	if (button == KEY_PLUS)
		matrix = get_scale_matrix(1 + scale_factor);
	else if (button == KEY_MINUS)
		matrix = get_scale_matrix(1 - scale_factor);
	else
		return ;
	for_each_point(map, apply_matrix, &matrix);
	draw_lines(mlx, map);
}

void	shear_map(int button, t_mlx *mlx, t_map *map)
{
	t_matrix	matrix;
	double		shear_factor;

	shear_factor = 100 / KEY_SENSITIVITY * M_PI / 90;
	if (button == KEY_Q)
		matrix = get_shear_matrix(shear_factor, 'x');
	else if (button == KEY_W)
		matrix = get_shear_matrix(-shear_factor, 'x');
	else if (button == KEY_A)
		matrix = get_shear_matrix(shear_factor, 'y');
	else if (button == KEY_S)
		matrix = get_shear_matrix(-shear_factor, 'y');
	else
		return ;
	for_each_point(map, apply_matrix, &matrix);
	draw_lines(mlx, map);
}

void	project_map(int button, t_mlx *mlx, t_map *map)
{
	void	(*projection)(t_point *, void *);

	if (button == KEY_C)
		projection = cavalier_projection;
	else if (button == KEY_I)
		projection = isometric_projection;
	else if (button == KEY_P)
		projection = perspective_projection;
	else
		return ;
	apply_projection(mlx, map, projection);
	draw_lines(mlx, map);
}
