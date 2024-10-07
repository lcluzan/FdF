#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"
#include "libft.h"

t_options	*parse_args(int ac, char **av)
{
	t_options	*options;

	if (ac != 2)
		return (NULL);
	options = malloc(sizeof(t_options));
	options->map_path = av[1];
	return (options);
}

void	display_usage(void)
{
	ft_putstr_fd("./fdf <filename>\n", 1);
}

int	main(int ac, char **av)
{
	t_options	*options;
	t_map		*map;

	options = parse_args(ac, av);
	if (!options)
	{
		display_usage();
		return (EXIT_FAILURE);
	}
	map = parse_map(options->map_path);
	if (!map)
		exit_with_error("Unknown error\n");
	printf("height %lu\nwidth %lu\n", map->height, map->width);
	draw(map);
	free_map(map);
	free(options);
	return (EXIT_SUCCESS);
}
