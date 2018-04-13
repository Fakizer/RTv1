/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 16:37:49 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 20:10:43 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_rtv1		*init_rtv1(char *scene)
{
	t_rtv1	*im;

	if ((im = (t_rtv1*)malloc(sizeof(t_rtv1))) == NULL)
		init_error("");
	im->mlx = NULL;
	im->win = NULL;
	im->rtv = NULL;
	im->rtv_data = NULL;
	im->scene_file = scene;
	im->screen_name = NULL;
	im->width = 0;
	im->height = 0;
	im->aspectratio = 0;
	im->bpp = 0;
	im->end = 0;
	im->size_line = 0;
	im->count_object = 0;
	im->num_light = 0;
	im->count_light = 0;
	im->num_object = 0;
	return (im);
}

t_vect		init_vect(double x, double y, double z)
{
	t_vect v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_ray		*init_ray(t_vect o, t_vect d)
{
	t_ray	*ray;

	ray = (t_ray*)malloc(sizeof(t_ray));
	ray->origin = o;
	ray->direction = d;
	return (ray);
}

void		init_cam_ray(t_camera *cam, t_rtv1 *im)
{
	if ((cam->ray = (t_ray*)malloc(sizeof(t_ray))) == NULL)
		init_error("");
	cam->ray->origin = cam->origin;
	cam->ray->direction = normalize(vectadd(negative(im->cam->wuv->cw),
		vectadd(vectmult(im->cam->wuv->cu, im->xyamnt->xamnt - 0.5),
			vectmult(negative(im->cam->wuv->cv), im->xyamnt->yamnt - 0.5))));
}
