/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:22:08 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/29 13:40:15 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_map(int button, t_mlx *mlx, t_map *map);
void	scale_map(int button, t_mlx *mlx, t_map *map);
void	shear_map(int button, t_mlx *mlx, t_map *map);
void	project_map(int button, t_mlx *mlx, t_map *map);

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

int	close_win(void *params)
{
	t_controls	*controls;

	controls = (t_controls *)params;
	mlx_destroy_image(controls->mlx->ptr, controls->mlx->img);
	mlx_clear_window(controls->mlx->ptr, controls->mlx->win);
	mlx_destroy_window(controls->mlx->ptr, controls->mlx->win);
	mlx_destroy_display(controls->mlx->ptr);
	free(controls->mlx->ptr);
	free(controls->mlx);
	free_map(controls->map);
	if (params != NULL)
		free(params);
	exit(0);
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
