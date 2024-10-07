#include "fdf.h"
#include <stdlib.h>

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

void	free_map(t_map *map)
{
	ft_lstclear(&map->lines, free);
	free(map->name);
	free(map);
}
