/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:23:44 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/21 12:23:45 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

t_mlx	*init_mlx(const char *name)
{
	char	*title;
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		exit_with_error("Failed to allocate memory");
	title = ft_strjoin("FdF - ", name);
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		exit_with_error("error connecting to graphics server");
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, title);
	if (!mlx->win)
		exit_with_error("error initializing window");
	free(title);
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!mlx->img)
		exit_with_error("error initializing image");
	mlx->data_addr = mlx_get_data_addr(
			mlx->img,
			&mlx->bpp,
			&mlx->size_line,
			&mlx->endian
			);
	return (mlx);
}

