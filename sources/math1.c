/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:52:41 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 19:48:04 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		coloradd(t_color c1, t_color c2)
{
	t_color cc;

	cc.r = (c1.r + c2.r) < 255 ? (c1.r + c2.r) : 255;
	cc.g = (c1.g + c2.g) < 255 ? (c1.g + c2.g) : 255;
	cc.b = (c1.b + c2.b) < 255 ? (c1.b + c2.b) : 255;
	return (cc);
}

t_vect		vectadd(t_vect vect, t_vect v)
{
	t_vect	vcopy;

	vcopy.x = vect.x + v.x;
	vcopy.y = vect.y + v.y;
	vcopy.z = vect.z + v.z;
	return (vcopy);
}

t_vect		vectmult(t_vect vect, double scalar)
{
	t_vect vcopy;

	vcopy.x = vect.x * scalar;
	vcopy.y = vect.y * scalar;
	vcopy.z = vect.z * scalar;
	return (vcopy);
}

t_vect		crossproduct(t_vect vect, t_vect v)
{
	t_vect vcopy;

	vcopy.x = vect.y * v.z - vect.z * v.y;
	vcopy.y = vect.z * v.x - vect.x * v.z;
	vcopy.z = vect.x * v.y - vect.y * v.x;
	return (vcopy);
}

t_vect		normalize(t_vect vect)
{
	double magn;
	t_vect vcopy;

	magn = magnitude(vect);
	vcopy.x = vect.x / magn;
	vcopy.y = vect.y / magn;
	vcopy.z = vect.z / magn;
	return (vcopy);
}
