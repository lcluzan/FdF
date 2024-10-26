/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:13:34 by lcluzan           #+#    #+#             */
/*   Updated: 2024/10/25 17:38:44 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
How matrix multiplication works (not 100% useful, but it took me so much time
so read it please):

m:
( a b c )
| d e f |
( g h i )

M:
( A B C )
| D E F |
( G H I )

v:
( x )
( y )
( z )

We'll multiple `v` by `m` and `M`. And study the result to understand how we can
multiply the 2 matrix together.
This way we can combine multiple matrix into a single one and improve
performances when we have to apply the matrix
to our whole map.

m * v:
( ax + by + cz )
| dx + ey + fz |
( gx + hy + iz )

M * (m * v):
( A(ax + by + cz) + B(dx + ey + fz) + C(gx + hy + iz) )
| D(ax + by + cz) + E(dx + ey + fz) + F(gx + hy + iz) |
( G(ax + by + cz) + H(dx + ey + fz) + I(gx + hy + iz) )

Then we develop:
( Aax + Aby + Acz + Bdx + Bey + Bfz + Cgx + Chy + Ciz )
| Dax + Dby + Dcz + Edx + Eey + Efz + Fgx + Fhy + Fiz |
( Gax + Gby + Gcz + Hdx + Hey + Hfz + Igx + Ihy + Iiz )

And we factorize by x, y and z:
( (Aa + Bd + Cg)x + (Ab + Be + Ch)y + (Ac + Bf + Ci)z )
| (Da + Ed + Fg)x + (Db + Ee + Fh)y + (Dc + Ef + Fi)z |
( (Ga + Hd + Ig)x + (Gb + He + Ih)y + (Gc + Hf + Ii)z )

Here we got a new vector in the form of a multiplication of a vector and matrix
(see m * v).
So we can deduce how to multiply the two matrices.
*/
/*
This function wrap the `multiply_vector_by_matrix` function to make it usable
with the `for_each_point`
function in `utils.c`.
*/
void	apply_matrix(t_point *point, void *params)
{
	t_matrix	matrix;

	matrix = *(t_matrix *)params;
	point->v = multiply_vector_by_matrix(point->v, matrix);
}

/*
Receive an axis and an angle in radians, and return the related rotation matrix.
If the axis is not valid (not x y or z) it will return the identity matrix that
has no effect when you multiply it to a vector.
*/
//the last matrix doen't have any effect
t_matrix	get_rotation_matrix(double rad, char axis)
{
	if (axis == 'x')
		return ((t_matrix){
			(t_vec){1, 0, 0},
			(t_vec){0, cos(rad), -sin(rad)},
			(t_vec){0, sin(rad), cos(rad)}
	});
	else if (axis == 'y')
		return ((t_matrix){
			(t_vec){cos(rad), 0, -sin(rad)},
			(t_vec){0, 1, 0},
			(t_vec){sin(rad), 0, cos(rad)}
	});
	else if (axis == 'z')
		return ((t_matrix){
			(t_vec){cos(rad), -sin(rad), 0},
			(t_vec){sin(rad), cos(rad), 0},
			(t_vec){0, 0, 1}
	});
	return ((t_matrix){
		(t_vec){1, 0, 0},
		(t_vec){0, 1, 0},
		(t_vec){0, 0, 1}
	});
}

t_matrix	get_shear_matrix(double rad, char axis)
{
	if (axis == 'x')
		return ((t_matrix){
			(t_vec){1, tan(rad), 0},
			(t_vec){0, 1, 0},
			(t_vec){0, 0, 1}
	});
	else if (axis == 'y')
		return ((t_matrix){
			(t_vec){1, 0, 0},
			(t_vec){tan(rad), 1, 0},
			(t_vec){0, 0, 1}
	});
	else if (axis == 'z')
		return ((t_matrix){
			(t_vec){1, 0, 0},
			(t_vec){0, 1, 0},
			(t_vec){tan(rad), 0, 1}
	});
	return ((t_matrix){
		(t_vec){1, 0, 0},
		(t_vec){0, 1, 0},
		(t_vec){0, 0, 1}
	});
}

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
