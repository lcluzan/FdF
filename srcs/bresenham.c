/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:12 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/21 12:54:05 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
Place a pixel on the screen and shift the coords to place the origin at the
center of the screen.

eg. If I want to draw the point (0,0) without shifting the coords, this point
would be located at the very top left
corner of the screen. So we shift the coords to have it in the middle
of the screen.

We also have to invert the y axis, cause in the mlx the y axis increase
by going down.

Shift coords to match the mlx origin at the top left corner of the screen

We make sure the pixel is not out the screen
*/
void	draw_pixel(t_mlx *mlx, t_point point)
{
	int		i;

	point.v.x += WIDTH / 2;
	point.v.y = HEIGHT / 2 - point.v.y;
	if (
		point.v.x >= 0
		&& point.v.x < WIDTH
		&& point.v.y >= 0
		&& point.v.y < HEIGHT
	)
	{
		i = (point.v.x * mlx->bpp / 8) + (point.v.y * mlx->size_line);
		mlx->data_addr[i] = point.color.b;
		mlx->data_addr[++i] = point.color.g;
		mlx->data_addr[++i] = point.color.r;
	}
}

void	bresenham_init(
	t_point points[2],
	t_vec *inc,
	int32_t d[2],
	int16_t *err
)
{
	if (points[0].v.x < points[1].v.x)
		inc->x = 1;
	else
		inc->x = -1;
	if (points[0].v.y < points[1].v.y)
		inc->y = 1;
	else
		inc->y = -1;
	d[0] = diff(points[1].v.x, points[0].v.x);
	d[1] = diff(points[1].v.y, points[0].v.y);
	*err = d[0] - d[1];
}

//Takes 2 points and draw a line using the bresenham algo
void	draw_line(t_mlx *mlx, t_point a, t_point b)
{
	int32_t	d[2];
	t_vec	inc;
	int16_t	err;
	int16_t	e2;

	bresenham_init((t_point[2]){a, b}, &inc, d, &err);
	while (true)
	{
		draw_pixel(mlx, a);
		if (a.v.x == b.v.x && a.v.y == b.v.y)
			break ;
		e2 = 2 * err;
		if (e2 > -d[1])
		{
			err -= d[1];
			a.v.x += inc.x;
		}
		if (e2 < d[0])
		{
			err += d[0];
			a.v.y += inc.y;
		}
	}
}
