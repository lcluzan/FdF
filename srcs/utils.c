#include <stdio.h>
#include <stdbool.h>
#include "fdf.h"
#include <math.h>

void	exit_with_error(const char *message)
{
	perror(message);
	exit(-1);
}

bool	is_hex_alpha(int c)
{
	if (c >= 'a' && c <= 'f')
		return (true);
	else
		return (false);
}

void	for_each_point(
	t_map *map,
	void (*fn)(t_point *point, void *params),
	void *params
)
{
	size_t	i;
	t_list	*map_line;

	map_line = map->lines;
	while (map_line)
	{
		i = 0;
		while (i < map->width)
		{
			fn(&((t_point *)map_line->content)[i], params);
			++i;
		}
		map_line = map_line->next;
	}
}

t_point	round_point(t_point p)
{
	p.v.x = round(p.v.x);
	p.v.y = round(p.v.y);
	p.v.z = round(p.v.z);
	return (p);
}

int	open_map(char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		exit_with_error("Failed to open the file");
	return (fd);
}
