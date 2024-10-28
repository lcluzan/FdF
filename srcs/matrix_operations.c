/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:15:16 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/28 16:15:29 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	get_scale_matrix(double s)
{
	return ((t_matrix){
		(t_vec){s, 0, 0},
		(t_vec){0, s, 0},
		(t_vec){0, 0, s}
	});
}

//Multiply a vector by a matrix
t_vec	multiply_vector_by_matrix(t_vec v, t_matrix m)
{
	t_vec	res;

	res.x = v.x * m.i.x + v.y * m.i.y + v.z * m.i.z;
	res.y = v.x * m.j.x + v.y * m.j.y + v.z * m.j.z;
	res.z = v.x * m.k.x + v.y * m.k.y + v.z * m.k.z;
	return (res);
}

//Multiply 2 matrices toether (see below for more details on how it works)
t_matrix	multiply_matrix_by_matrix(t_matrix m1, t_matrix m2)
{
	t_matrix	res;

	res.i.x = m1.i.x * m2.i.x + m1.i.y * m2.j.x + m1.i.z * m2.k.x;
	res.i.y = m1.i.x * m2.i.y + m1.i.y * m2.j.y + m1.i.z * m2.k.y;
	res.i.z = m1.i.x * m2.i.z + m1.i.y * m2.j.z + m1.i.z * m2.k.z;
	res.j.x = m1.j.x * m2.i.x + m1.j.y * m2.j.x + m1.j.z * m2.k.x;
	res.j.y = m1.j.x * m2.i.y + m1.j.y * m2.j.y + m1.j.z * m2.k.y;
	res.j.z = m1.j.x * m2.i.z + m1.j.y * m2.j.z + m1.j.z * m2.k.z;
	res.k.x = m1.k.x * m2.i.x + m1.k.y * m2.j.x + m1.k.z * m2.k.x;
	res.k.y = m1.k.x * m2.i.y + m1.k.y * m2.j.y + m1.k.z * m2.k.y;
	res.k.z = m1.k.x * m2.i.z + m1.k.y * m2.j.z + m1.k.z * m2.k.z;
	return (res);
}
