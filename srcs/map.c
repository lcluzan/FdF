/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:23:26 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/26 16:08:17 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Safely allocate a map struct and initialize some fields.
// allocate and init map
t_map	*new_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		exit_with_error("Failed to allocate memory");
	map->height = 0;
	map->width = 0;
	map->lines = NULL;
	return (map);
}

//Free a map and all its content without memory leaks.
void	free_map(t_map *map)
{
	ft_lstclear(&map->lines, free);
	ft_lstclear(&map->unprojected_lines, free);
	free(map->name);
	free(map);
}
