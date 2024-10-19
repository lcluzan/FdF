/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:15:42 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/19 19:15:47 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_down(int button, int x, int y, void *params)
{
	t_controls	*controls;

	controls = (t_controls *)params;
	if (
		button == MOUSE_CLICK_LEFT
		|| button == MOUSE_CLICK_RIGHT
		|| button == MOUSE_CLICK_MIDDLE
	)
	{
		controls->mouse.pos.x = x;
		controls->mouse.pos.y = y;
		controls->mouse.is_down = true;
	}
	return (0);
}

int	mouse_up(int button, int x, int y, void *params)
{
	t_controls	*controls;

	controls = (t_controls *)params;
	(void)x;
	(void)y;
	if (
		button == MOUSE_CLICK_LEFT
		|| button == MOUSE_CLICK_RIGHT
		|| button == MOUSE_CLICK_MIDDLE
	)
	{
		controls->mouse.pos.x = 0;
		controls->mouse.pos.y = 0;
		controls->mouse.is_down = false;
	}
	return (0);
}

int	mouse_move(int x, int y, void *params)
{
	t_controls	*controls;
	double		x_angle;
	double		y_angle;
	t_matrix	matrix;

	controls = (t_controls *)params;
	if (!controls->mouse.is_down)
		return (0);
	y_angle = (double)(controls->mouse.pos.x - x) / MOUSE_SENSITIVITY;
	x_angle = (double)(y - controls->mouse.pos.y) / MOUSE_SENSITIVITY;
	matrix = multiply_matrix_by_matrix(
			get_rotation_matrix(y_angle, 'y'),
			get_rotation_matrix(x_angle, 'x')
			);
	for_each_point(controls->map, apply_matrix, &matrix);
	draw_lines(controls->mlx, controls->map);
	controls->mouse.pos.x = x;
	controls->mouse.pos.y = y;
	return (0);
}
