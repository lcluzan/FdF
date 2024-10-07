#include "fdf.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

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
int	close_win(void *params)
{
	if (params != NULL)
		free (params);
	exit (0);
}
t_controls	*listen_events(t_mlx *mlx, t_map *map)
{
	t_controls	*controls;

	controls = new_controls(mlx, map);
	mlx_hook(mlx->win, MotionNotify, PointerMotionMask, mouse_move, controls);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, mouse_down, controls);
	mlx_hook(mlx->win, ButtonRelease, ButtonReleaseMask, mouse_up, controls);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, close_win, controls);
	return (controls);
}
