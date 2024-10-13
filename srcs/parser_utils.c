#include "fdf.h"

#define HEX_PREFIX "0x"
#define MAX_COLOR 0xffffff

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