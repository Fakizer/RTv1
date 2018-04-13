/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 13:06:13 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 19:48:03 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect		negative(t_vect vect)
{
	t_vect vcopy;

	vcopy.x = -vect.x;
	vcopy.y = -vect.y;
	vcopy.z = -vect.z;
	return (vcopy);
}

double		dotproduct(t_vect ray, t_vect normal)
{
	return (ray.x * normal.x + ray.y * normal.y + ray.z * normal.z);
}

t_vect		get_normal_sphere(t_vect intersection_position, t_vect origin)
{
	t_vect	vect;

	vect = normalize(vectadd(intersection_position, negative(origin)));
	return (vect);
}

t_vect		get_normal_cylinder(t_vect int_pos, t_ray *ray, t_cylinder *obj)
{
	double	m;
	t_vect	vect;

	m = dotproduct(ray->direction, obj->normal) * obj->t +
		dotproduct(vectadd((ray->origin), negative(obj->origin)), obj->normal);
	vect = vectadd(vectadd(int_pos, negative(obj->origin)),
		negative(vectmult(obj->normal, m)));
	return (normalize((vect)));
}

t_vect		get_normal_cone(t_vect int_pos, t_ray *ray, t_cone *obj)
{
	double	m;
	double	k;
	t_vect	vect;

	k = tan(obj->angle * M_PI / 180);
	m = dotproduct(ray->direction, obj->normal) * obj->t +
		dotproduct(vectadd((ray->origin), negative(obj->origin)), obj->normal);
	vect = normalize(vectadd(vectadd(int_pos, negative(obj->origin)),
			negative(vectmult(vectmult(obj->normal, m), (1 + k * k)))));
	return (vect);
}
