#include "fdf.h"
#include "libft.h"
#include <sys/fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

t_point	parse_map_point(char *raw_map_point)
{
	t_point	point;
	char	**splitted_map_point;

	splitted_map_point = ft_strsplit(raw_map_point, ',');
	if (!splitted_map_point)
		exit_with_error("Failed to parse map");
	if (!parse_height(splitted_map_point[0], &point.v.z))
		exit_with_error("Failed to parse map");
	if (splitted_map_point[1])
	{
		if (!parse_color(splitted_map_point[1], &point.color))
			exit_with_error("Failed to parse map");
	}
	else
		point.color = WHITE;
	if (splitted_map_point[1] && splitted_map_point[2])
		exit_with_error("Failed to parse map");
	return (point);
}

t_point	*parse_line(char *raw_line, size_t row, size_t *width)
{
	char	**splitted_line;
	t_point	*line;
	int		i;

	splitted_line = ft_strsplit(raw_line, ' ');
	*width = 0;
	while (splitted_line[*width])
		++*width;
	line = malloc(sizeof(t_point) * *width);
	i = 0;
	while (splitted_line[i])
	{
		line[i] = parse_map_point(splitted_line[i]);
		line[i].v.x = i;
		line[i].v.y = -(int)row;
		++i;
	}
	return (line);
}

bool	parse_raw_line(t_map *map, int fd, size_t *tmp_width)
{
	char	*raw_line;
	t_list	*line;

	raw_line = get_next_line(fd);
	if (!raw_line)
		return (false);
	line = ft_lstnew(parse_line(raw_line, map->height, tmp_width));
	if (!map->lines)
	{
		map->lines = line;
		map->width = *tmp_width;
	}
	else
	{
		if (map->width != *tmp_width)
			exit_with_error("Invalid map");
		ft_lstadd_front(&map->lines, line);
	}
	++map->height;
	free(raw_line);
	return (true);
}

t_map	*parse_map(char *map_path)
{
	int		fd;
	t_map	*map;
	size_t	tmp_width;

	fd = open_map(map_path);
	map = new_map();
	while (true)
	{
		if (!parse_raw_line(map, fd, &tmp_width))
			break ;
	}
	map->scale = (double)min(WIDTH / map->width / 2, HEIGHT / map->height / 2);
	map->offset.x = -(((double)map->width - 1) / 2);
	map->offset.y = ((double)map->height - 1) / 2;
	map->name = ft_strdup(map_path);
	return (map);
}
