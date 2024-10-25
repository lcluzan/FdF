/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:31 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/25 15:57:57 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

/*
This function makes sure that the program args are valid and if so,
it will returned them parsed as an `options` struct.
verify args length
allocate options
fill options
return options
*/
t_options	*parse_args(int ac, char **av)
{
	t_options	*options;

	if (ac != 2)
		return (NULL);
	options = malloc(sizeof(t_options));
	options->map_path = av[1];
	return (options);
}

//Just display the program usage (you're welcome)
void	display_usage(void)
{
	ft_putstr_fd("./fdf <filename>\n", 1);
}

/**
Enrtypoint of the program, but you already knew that.parse and verify args
parse map
display height and width
this should be called when the mlx closing window event is fired.
So this code is actually leaking, but nvm
its puprpose is not to show you how to manage this.
*/
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
