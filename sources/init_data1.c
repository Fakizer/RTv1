/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:57:03 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 20:06:56 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		init_color(t_tsvet r, t_tsvet g, t_tsvet b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

void		init_gxgygz(t_rtv1 *im)
{
	im->xyz = (t_xyz*)malloc(sizeof(t_xyz));
	im->xyz->gx = init_vect(1, 0, 0);
	im->xyz->gy = init_vect(0, 1, 0);
	im->xyz->gz = init_vect(0, 0, 1);
}

void		init_cwcucv(t_camera *cam, t_xyz *xyz)
{
	if (cam->origin.x == 0 && cam->origin.y == 0)
		xyz->gz = negative(xyz->gx);
	cam->wuv = (t_wuv*)malloc(sizeof(t_wuv));
	cam->wuv->cw = normalize(vectadd(cam->origin, negative(cam->look_at)));
	cam->wuv->cu = normalize(crossproduct(negative(cam->wuv->cw), xyz->gz));
	cam->wuv->cv = crossproduct(negative(cam->wuv->cw), cam->wuv->cu);
}

void		init_xyamnt(t_rtv1 *im, int x, int y)
{
	im->xyamnt = (t_amnt*)malloc(sizeof(t_amnt));
	if (im->width > im->height)
	{
		im->xyamnt->xamnt = ((x + 0.5) / im->width) * im->aspectratio -
		(((im->width - im->height) / (double)im->height) / 2);
		im->xyamnt->yamnt = ((im->height - y) + 0.5) / im->height;
	}
	else if (im->width < im->height)
	{
		im->xyamnt->xamnt = (x + 0.5) / im->width;
		im->xyamnt->yamnt = (((im->height - y) + 0.5) / im->height) /
		im->aspectratio - (((im->height - im->width) / (double)im->width) / 2);
	}
	else
	{
		im->xyamnt->xamnt = ((double)x + 0.5) / (double)im->width;
		im->xyamnt->yamnt = ((double)(im->height - y) + 0.5) /
		(double)im->height;
	}
}

void		check_inter(t_rtv1 *im)
{
	int		index;

	im->inter = (t_inter*)malloc(sizeof(t_inter));
	im->inter->inters = (double*)malloc(sizeof(double) *
		im->num_object);
	index = 0;
	while (index < im->num_object)
	{
		if (ft_strstr(im->object[index].obj_name, "sphere"))
			im->inter->inters[index] =
		find_int_sp(im->object[index].sphere, im->cam->ray);
		if (ft_strstr(im->object[index].obj_name, "plane"))
			im->inter->inters[index] =
		find_int_pl(im->object[index].plane, im->cam->ray);
		if (ft_strstr(im->object[index].obj_name, "cone"))
			im->inter->inters[index] =
		find_int_co(im->object[index].cone, im->cam->ray);
		if (ft_strstr(im->object[index].obj_name, "cylinder"))
			im->inter->inters[index] =
		find_int_cyl(im->object[index].cylinder, im->cam->ray);
		index++;
	}
	im->inter->index_of_wo = win_obj_ind(im->inter->inters, im);
}
