/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:24:05 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/24 18:18:19 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//abort the program with an error message.
void	exit_with_error(const char *message)
{
	perror(message);
	exit(-1);
}

//check that a character is alphabetic and valid in an hex string (basically
// if it's either a, b, c, d, e, or f).
bool	is_hex_alpha(int c)
{
	if (c >= 'a' && c <= 'f')
		return (true);
	else
		return (false);
}

/*
  This function will loop through each point of a map, and call the function
  passed in parameters `fn`.
  Passing to this function a pointer on the point, and the paramter `params`.

  This way we can apply some specific changes to every points of the map without
   having to write the same looping logic
  every time.
*/
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

//round a point coords
t_point	round_point(t_point p)
{
	p.v.x = round(p.v.x);
	p.v.y = round(p.v.y);
	p.v.z = round(p.v.z);
	return (p);
}

//Just open a file and make sure it worked.
int	open_map(char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		exit_with_error("Failed to open the file");
	return (fd);
}
