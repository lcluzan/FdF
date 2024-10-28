/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:22:08 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/28 14:46:11 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

//Safely allocate a control struct and initialize some fields.
//allocate and init map
t_controls	*new_controls(t_mlx *mlx, t_map *map)
{
	t_controls	*controls;

	controls = malloc(sizeof(t_controls));
	if (!controls)
		exit_with_error("Failed to allocate memory");
	controls->mouse.is_down = false;
	controls->mouse.pos.x = 0;
	controls->mouse.pos.y = 0;
	controls->map = map;
	controls->mlx = mlx;
	return (controls);
}

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

int	close_win(void *params)
{
	t_controls	*controls;

	controls = (t_controls *)params;
	mlx_destroy_image(controls->mlx->ptr, controls->mlx->img);
	mlx_destroy_window(controls->mlx->ptr, controls->mlx->win);
	free_map(controls->map);
	if (params != NULL)
		free(params);
	exit(0);
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

int	key_press(int button, void *params)
{
	t_controls	*controls;

	controls = (t_controls *)params;
	if (button == KEY_LEFT || button == KEY_UP || button == KEY_RIGHT
		|| button == KEY_DOWN)
		translate_map(button, controls->mlx, controls->map);
	else if (button == KEY_ESC)
		close_win(params);
	else if (button == KEY_PLUS || button == KEY_MINUS)
		scale_map(button, controls->mlx, controls->map);
	else if (button == KEY_Q || button == KEY_W || button == KEY_A
		|| button == KEY_S)
		shear_map(button, controls->mlx, controls->map);
	else if (button == KEY_P || button == KEY_I || button == KEY_C)
		project_map(button, controls->mlx, controls->map);
	return (0);
}

/*
This function will create a control struct, and subscribe to various mlx events.
Meaning a function will be called according to what happen on the computer
(eg. keyboard is pressed, window is closed, mouse is moved, etc.)
For each kind of event, our custom function will also receive a parameter.
Here we'll pass the control struct,
containing our map, mlx pointer and some more data that will be used to
redraw the map.
*/
// allocate and init controls
// add mouse listeners
t_controls	*listen_events(t_mlx *mlx, t_map *map)
{
	t_controls	*controls;

	controls = new_controls(mlx, map);
	mlx_hook(mlx->win, MotionNotify, PointerMotionMask, mouse_move, controls);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, mouse_down, controls);
	mlx_hook(mlx->win, ButtonRelease, ButtonReleaseMask, mouse_up, controls);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, close_win, controls);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, key_press, controls);
	return (controls);
}
