/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 16:30:01 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 20:44:30 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		img_pixel_put(int x, int y, t_color color, t_rtv1 *im)
{
	if (x >= 0 && y >= 0 && x < im->width && y < im->height)
	{
		if (im->end == MY_LITTLE_END)
		{
			im->rtv_data[(y * im->size_line) + ((im->bpp / 8) * x)] = color.b;
			im->rtv_data[(y * im->size_line) + ((im->bpp / 8) * x) + 1] =
			color.g;
			im->rtv_data[(y * im->size_line) + ((im->bpp / 8) * x) + 2] =
			color.r;
		}
		else if (im->end == MY_BIG_END)
		{
			im->rtv_data[(y * im->size_line) + ((im->bpp / 8) * x) + 1] =
			color.r;
			im->rtv_data[(y * im->size_line) + ((im->bpp / 8) * x) + 2] =
			color.g;
			im->rtv_data[(y * im->size_line) + ((im->bpp / 8) * x) + 3] =
			color.b;
		}
		else
			init_error(ERROR_END);
	}
}

void		get_normal(t_rtv1 *im, t_object *obj, t_ray *ray)
{
	if (ft_strstr(obj->obj_name, "sphere"))
		obj->normal = get_normal_sphere(im->inter->int_pos,
			obj->sphere->origin);
	if (ft_strstr(obj->obj_name, "plane"))
		obj->normal = obj->plane->normal;
	if (ft_strstr(obj->obj_name, "cylinder"))
		obj->normal = get_normal_cylinder(im->inter->int_pos, ray,
			obj->cylinder);
	if (ft_strstr(obj->obj_name, "cone"))
		obj->normal = get_normal_cone(im->inter->int_pos, ray, obj->cone);
}

t_color		set_color(t_rtv1 *im, t_object *obj, t_light *light, t_ray *ray)
{
	t_color		c1;
	t_color		c2;
	t_vect		l;
	t_vect		p;
	double		gcp;

	get_normal(im, obj, ray);
	l = normalize(vectadd(light->position, negative(im->inter->int_pos)));
	gcp = dotproduct(l, obj->normal) / im->num_light;
	gcp = gcp < 0 ? 0 : gcp;
	gcp = gcp > 1 ? 1 : gcp;
	c1 = init_color(obj->color.r * gcp, obj->color.g * gcp,
		obj->color.b * gcp);
	p = normalize(vectadd(l, negative(ray->direction)));
	gcp = dotproduct(p, obj->normal);
	gcp = gcp > 1 ? 1 : gcp;
	if (gcp >= light->bl && gcp < 1)
		gcp = 1.0 - ((1.0 - gcp) / (1 - light->bl));
	else
		gcp = 0;
	c2 = init_color(255 * gcp, 255 * gcp, 255 * gcp);
	return (coloradd(c1, c2));
}

int			ishadow(int ind, double *inters, t_light *light, t_vect pos)
{
	if (ind > -1)
	{
		if (inters[ind] <=
			magnitude(vectadd(light->position, negative(pos))))
		{
			free(inters);
			return (0);
		}
		else
		{
			free(inters);
			return (1);
		}
	}
	else
	{
		free(inters);
		return (1);
	}
}

int			shadow(t_rtv1 *im, t_light *light, t_vect int_pos, int ind)
{
	int		index;
	double	*inters;
	t_ray	*ray;
	int		ind_of_wo;

	ind_of_wo = 0;
	ray = init_ray(int_pos,
		normalize(vectadd(light->position, negative(int_pos))));
	inters = (double*)malloc(sizeof(double) * im->num_object);
	index = -1;
	while (++index < im->num_object)
	{
		if (ft_strstr(im->object[index].obj_name, "sphere") ||
			ft_strstr(im->object[index].obj_name, "plane"))
			inters[index] = sp_pl(&(im->object[index]), ray, index, ind);
		if (ft_strstr(im->object[index].obj_name, "cone") ||
			ft_strstr(im->object[index].obj_name, "cylinder"))
			inters[index] = co_cy(&(im->object[index]), ray, index, ind);
	}
	free(ray);
	ind_of_wo = win_obj_ind(inters, im);
	if (ishadow(ind_of_wo, inters, light, int_pos))
		return (1);
	else
		return (0);
}
