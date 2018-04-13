/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findintersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 13:28:45 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 19:48:16 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_int_co1(double a, double b, double c)
{
	double d;
	double t1;
	double t2;

	d = 0;
	t1 = 0;
	t2 = 0;
	d = (b * b) - (4.0 * a * c);
	if (d > 0)
	{
		d = sqrt(d);
		t1 = (-b - d) / (2 * a);
		t2 = (-b + d) / (2 * a);
		d = t1 < t2 ? t1 : t2;
		if (d > 1e-6)
			return (d);
		else
			return (-1);
	}
	else
		return (-1);
}

double		find_int_co(t_cone *cone, t_ray *ray)
{
	double	a;
	double	b;
	double	c;
	double	k;
	t_vect	x;

	a = 0;
	b = 0;
	c = 0;
	k = tan(cone->angle * M_PI / 180);
	x = vectadd(ray->origin, negative(cone->origin));
	a = dotproduct(ray->direction, ray->direction) - (1 + k * k) *
		dotproduct(ray->direction, cone->normal) * dotproduct(ray->direction,
			cone->normal);
	b = 2 * (dotproduct(ray->direction, x) - (1 + k * k) *
			dotproduct(ray->direction, cone->normal) * dotproduct(x,
				cone->normal));
	c = dotproduct(x, x) - (1 + k * k) * dotproduct(x, cone->normal) *
			dotproduct(x, cone->normal);
	return (cone->t = find_int_co1(a, b, c));
}

double		find_int_cyl1(double a, double b, double c)
{
	double d;
	double t1;
	double t2;

	d = 0;
	t1 = 0;
	t2 = 0;
	d = (b * b) - (4.0 * a * c);
	if (d > 0)
	{
		d = sqrt(d);
		t1 = (-b - d) / (2 * a);
		t2 = (-b + d) / (2 * a);
		d = t1 < t2 ? t1 : t2;
		if (d > 1e-6)
			return (d);
		else
			return (-1);
	}
	else
		return (-1);
}

double		find_int_cyl(t_cylinder *cylinder, t_ray *ray)
{
	double	a;
	double	b;
	double	c;
	t_vect	delta;

	a = 0;
	b = 0;
	c = 0;
	cylinder->t = 0;
	delta = (vectadd(ray->origin, negative(cylinder->origin)));
	a = dotproduct(vectadd(ray->direction, negative(vectmult(cylinder->normal,
	dotproduct(ray->direction, cylinder->normal)))), vectadd(ray->direction,
	negative(vectmult(cylinder->normal, dotproduct(ray->direction,
		cylinder->normal)))));
	b = 2 * dotproduct(vectadd(ray->direction, negative(vectmult(
		cylinder->normal, dotproduct(ray->direction, cylinder->normal)))),
	vectadd(delta, negative(vectmult(cylinder->normal, dotproduct(delta,
		cylinder->normal)))));
	c = dotproduct(vectadd(delta, negative(vectmult(cylinder->normal,
		dotproduct(delta, cylinder->normal)))), vectadd(delta, negative(
	vectmult(cylinder->normal, dotproduct(delta, cylinder->normal))))) -
	(cylinder->diameter * cylinder->diameter / 4);
	return (cylinder->t = find_int_cyl1(a, b, c));
}

double		find_int_sp(t_sphere *sphere, t_ray *ray)
{
	double	b;
	double	c;
	double	d;
	double	root;
	t_vect	asd;

	root = 0;
	asd = vectadd(ray->origin, negative(sphere->origin));
	b = 2 * dotproduct(asd, ray->direction);
	c = dotproduct(asd, asd) - (sphere->diameter * sphere->diameter / 4);
	d = (b * b) - (4 * c);
	if (d > 0)
	{
		root = (-b - sqrt(d)) / 2;
		if (root > 1e-6)
			return (root);
		else
		{
			root = (-b + sqrt(d)) / 2;
			return (root > 1e-6);
		}
	}
	else
		return (-1);
}
