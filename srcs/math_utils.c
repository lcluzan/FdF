#include "fdf.h"

int32_t	abs(int32_t n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

int32_t	min(int32_t a, int32_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int32_t	max(int32_t a, int32_t b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int32_t	diff(int32_t a, int32_t b)
{
	if ((a < 0 && b < 0) || (a >= 0 && b >= 0))
		return (abs(abs(a) - abs(b)));
	else
		return (abs(a) + abs(b));
}
