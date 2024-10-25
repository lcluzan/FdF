/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:15:42 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/25 16:09:18 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//
// Mouse controls
//

/*
This function is called when the user iniate a click. It will save the position
of the click and save the mouse status as "down"
*/
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

/*
This function is called when the user release a click. It will reset the saved
position of the mouse to 0 and save the mouse status as "up"
*/
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

/*
This function is called when the user move the mouse. If the mouse is "up"
nothing will happen.
But if the mouse is down, according to the difference between the previous mouse
position and the current one.
2 matrix will be computed.

The first one will be a rotation matrix on the `y` axis, with an angle depending
on the distance traveled by the mouse on the `x` axis.

The second one will be a rotation matrix on the `x` axis, with an angle
depending on the distance traveled by the mouse on the `y` axis.

Once computed, these matrix will be multiplied together to form a single
rotation matrix. Then, each point of the map will be multiplied by this matrix.
And the screen will be redrawn.
And last, the saved mouse position is updated.
do nothing if mouse is not down
compute rotation angle for both axis according and divide this angle by the
mouse sensitivity.
get the final matrix by multiplying the 2 previous ones together
use this util to call the `apply_matrix` function on each point of the map with
the previous matrix parameter.
here we pass a pointer on the matrix, and not the matrix directly because the
`for_each_point` takes a `void *` as
a parameter to allow any kind of data to be sent. Thus we have to wrap our
matrix into a pointer too.
call the drawing function again to redraw the screen.
update saved mouse position
*/

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
