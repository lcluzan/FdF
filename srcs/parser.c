/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:23:59 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/29 13:54:50 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"

/*Return a `point` struct parsed from a string with such a format `y,color`
(eg. `1,0xff`)
split raw point by comma
check and parse height
check and parse color
assert that there's no useless data (meaning more than one comma)
*/
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
	{
		point.color.r = 0xff;
		point.color.g = 0xff;
		point.color.b = 0xff;
	}
	if (splitted_map_point[1] && splitted_map_point[2])
		exit_with_error("Failed to parse map");
	free_split(splitted_map_point);
	return (point);
}

/*
parse a full line from a map file and send an array of `point` struct.
It will also put the width of the line in the `width` paramter.

The row parameter is used to fill the `y` value of each point.

split raw line by space
get width
allocate line
fill line with x y z coords.
we reverse the row value cause' in classic geometry, as the y axis goes up,
the y value increase, but in such a map it's the opposite, the line count
increase by going down in the map file
*/
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
	if (!line)
		exit_with_error("Failed to allocate memory");
	i = 0;
	while (splitted_line[i])
	{
		line[i] = parse_map_point(splitted_line[i]);
		line[i].v.x = i;
		line[i].v.y = -(int)row;
		++i;
	}
	free_split(splitted_line);
	return (line);
}

/*
This function will read a line from the map file, parse it and add it to the
chained list of lines.
It will also check if the width of the map is consistent. If not, it will exit
the program.
*/
bool	parse_raw_line(t_map *map, int fd, size_t *tmp_width)
{
	char	*raw_line;
	t_list	*line;

	raw_line = get_next_line(fd);
	if (!raw_line)
		return (false);
	(void)tmp_width;
	line = ft_lstnew(parse_line(raw_line, map->height, tmp_width));
	if (!map->unprojected_lines)
	{
		map->unprojected_lines = line;
		map->width = *tmp_width;
	}
	else
	{
		if (map->width != *tmp_width)
			exit_with_error("Invalid map");
		ft_lstadd_front(&map->unprojected_lines, line);
	}
	++map->height;
	free(raw_line);
	return (true);
}

/*
This function receives a map file path, opens it and parse its content to
return a `map` struct.
It will also compute a scale and offset value.

the smaller the map is, the bigger the scale will be. This value will be used
later in the `draw.c` file to
zoom in the map and make it fill the screen. So it's computed using the screen
size, and map size.

The offset will be used like the scale value to shift the map coords to the
center of the screen.
The way we parse the map, the origin is in the top left corner, so we'll shift
the coords to have the origin
in the middle of the map.

Also we use a chained list to avoid having to read the map file twice. A first
time to get the height of the map
by reading each line, then allocate the right size for the map, and then read it
 a second time to fill this map.
Anyway, it's not mandatory, and it's a discutable design choice.

open file
create new map
get all lines
parse line
fill map
if it's the first line, we save the width and the line.
if it's not the first line, we make sure that thw width is still the same
and we add this line to the chained list.
increase height
here we free the gnl line.
compute scale and offset values.
also save the map name as the map path. It will be used as the title of our
program window.
*/
t_map	*parse_map(t_options *options)
{
	int		fd;
	t_map	*map;
	size_t	tmp_width;

	fd = open_map(options);
	map = new_map();
	while (true)
	{
		if (!parse_raw_line(map, fd, &tmp_width))
			break ;
	}
	close(fd);
	map->scale = (double)min(WIDTH / map->width / 2, HEIGHT / map->height / 2);
	map->offset.x = -(((double)map->width - 1) / 2);
	map->offset.y = ((double)map->height - 1) / 2;
	map->name = ft_strdup(options->map_path);
	return (map);
}
