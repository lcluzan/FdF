/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:23:37 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/24 18:21:16 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//return the absolute value.
int32_t	abs(int32_t n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

//return the smallest value between 2 parameters.
int32_t	min(int32_t a, int32_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

//return the largest value between 2 parameters.
int32_t	max(int32_t a, int32_t b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
//compute the distance between 2 signed values (eg. diff(-2, 1) = 3)
int32_t	diff(int32_t a, int32_t b)
{
	if ((a < 0 && b < 0) || (a >= 0 && b >= 0))
		return (abs(abs(a) - abs(b)));
	else
		return (abs(a) + abs(b));
}
