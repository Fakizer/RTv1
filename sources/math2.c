/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:54:05 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 19:48:12 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		magnitude(t_vect vect)
{
	return (sqrt((vect.x * vect.x) + (vect.y * vect.y) +
		(vect.z * vect.z)));
}

double		find_int_pl(t_plane *plane, t_ray *ray)
{
	double	a;
	double	b;

	a = 0;
	b = 0;
	a = dotproduct(ray->direction, plane->normal);
	if (a != 0)
		b = -1 * (dotproduct(vectadd(ray->origin, negative(plane->origin)),
			plane->normal)) / a;
	if (b > 1e-6)
		return (b);
	else
		return (-1);
}

double		sp_pl(t_object *obj, t_ray *ray, int index, int ind)
{
	int		inters;

	inters = 0;
	if (ft_strstr(obj->obj_name, "sphere"))
		inters =
			find_int_sp(obj->sphere, ray);
	if (ft_strstr(obj->obj_name, "plane"))
	{
		if (index == ind)
			inters = -1;
		else
			inters =
				find_int_pl(obj->plane, ray);
	}
	return (inters);
}

double		co_cy(t_object *obj, t_ray *ray, int index, int ind)
{
	int		inters;

	inters = 0;
	if (ft_strstr(obj->obj_name, "cone"))
	{
		if (index == ind)
			inters = -1;
		else
			inters =
				find_int_co(obj->cone, ray);
	}
	if (ft_strstr(obj->obj_name, "cylinder"))
	{
		if (index == ind)
			inters = -1;
		else
			inters =
				find_int_cyl(obj->cylinder, ray);
	}
	return (inters);
}
