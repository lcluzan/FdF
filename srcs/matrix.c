#include "fdf.h"
#include <math.h>

void	apply_matrix(t_point *point, void *params)
{
	t_matrix	matrix;

	matrix = *(t_matrix *)params;
	point->v = multiply_vector_by_matrix(point->v, matrix);
}

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

t_vec	multiply_vector_by_matrix(t_vec v, t_matrix m)
{
	t_vec	res;

	res.x = v.x * m.i.x + v.y * m.i.y + v.z * m.i.z;
	res.y = v.x * m.j.x + v.y * m.j.y + v.z * m.j.z;
	res.z = v.x * m.k.x + v.y * m.k.y + v.z * m.k.z;
	return (res);
}

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
