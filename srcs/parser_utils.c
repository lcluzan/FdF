/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:23:50 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/27 17:08:00 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define HEX_PREFIX "0x"
#define MAX_COLOR 0xffffff

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

/*
  Just an ugly atoi, if the parsing is successful, it returns true, otherwise,
	false.and the result if put in the `height` parameter.
*/
// sign support
// fail if empty
// check on digits
// parse each digit
// assert height won't overflow (15 instead of 16 for the sign bit)
// save height and change sign if needed
bool	parse_height(char *str, double *height)
{
	int32_t	num;
	bool	is_neg;

	if (!str)
		return (false);
	is_neg = false;
	if (*str == '-')
	{
		++str;
		is_neg = true;
	}
	if (!*str)
		return (false);
	num = 0;
	while (*str)
	{
		if (!ft_isdigit((int)*str))
			return (false);
		num = num * 10 + (int32_t)(*str - '0');
		if (num && (num - is_neg) >> 15)
			return (false);
		++str;
	}
	*height = (double)((num ^ -is_neg) + is_neg);
	return (true);
}

/*
  Same as above but it parse and hex string to generate a color struct.
  Note that it doesn't support uppercase hex. Thus some maps are not working.
  But anyway, this function is crap, and the one above too.
  And you already have that part working in your own fdf.
*/
// check on hex prefix
// fail if empty
// check on hex digits and max length
// parse each digit
// assert max color has not been reached
// decompose hex to color struct
bool	parse_color(char *str, t_color *color)
{
	u_int32_t	hex;

	if (!str || ft_strncmp(str, HEX_PREFIX, ft_strlen(HEX_PREFIX)) != 0)
		return (false);
	str += ft_strlen(HEX_PREFIX);
	if (!*str)
		return (false);
	hex = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
			hex = hex * 16 + (u_int32_t)(*str - '0');
		else if (is_hex_alpha(*str))
			hex = hex * 16 + (u_int32_t)(*str - 'a' + 10);
		else
			return (false);
		if (hex > MAX_COLOR)
			return (false);
		++str;
	}
	color->r = hex >> 16;
	color->g = (hex >> 8) & 0xff;
	color->b = hex & 0xff;
	return (true);
}
