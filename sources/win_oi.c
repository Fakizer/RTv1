/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_oi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:49:02 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 19:48:13 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				win_obj_ind2(double *object_int, t_rtv1 *im, double max)
{
	int index;
	int ind_of_mv;

	index = 0;
	ind_of_mv = 0;
	if (max > 0)
	{
		while (index < im->num_object)
		{
			if (object_int[index] > 0 && object_int[index] <= max)
			{
				max = object_int[index];
				ind_of_mv = index;
			}
			index++;
		}
		return (ind_of_mv);
	}
	else
		return (-1);
}

int				win_obj_ind1(double *object_int, t_rtv1 *im)
{
	int		ind_of_mv;
	int		i;
	int		index;
	double	max;

	index = 0;
	i = 0;
	ind_of_mv = 0;
	max = 0;
	while (i < im->num_object)
	{
		if (max < object_int[i])
			max = object_int[i];
		i++;
	}
	ind_of_mv = win_obj_ind2(object_int, im, max);
	if (ind_of_mv == -1)
		return (-1);
	else
		return (ind_of_mv);
}

int				win_obj_ind(double *object_int, t_rtv1 *im)
{
	int ind_of_mv;

	ind_of_mv = 0;
	if (im->num_object == 0)
		return (-1);
	else if (im->num_object == 1)
	{
		if (object_int[0] > 0)
			return (0);
		else
			return (-1);
	}
	else
	{
		ind_of_mv = win_obj_ind1(object_int, im);
		if (ind_of_mv == -1)
			return (-1);
		else
			return (ind_of_mv);
	}
}

void			prelst(t_rtv1 *im, int x, int y)
{
	int		index;
	t_color color_light;
	t_color final_color;

	index = 0;
	final_color = init_color(0, 0, 0);
	while (index < im->num_light)
	{
		if (!(shadow(im, &(im->light[index]), im->inter->int_pos,
			im->inter->index_of_wo)))
			color_light = init_color(0, 0, 0);
		else
			color_light = set_color(im, &(im->object[im->inter->index_of_wo]),
				&(im->light[index]), im->cam->ray);
		final_color = coloradd(final_color, color_light);
		index++;
	}
	img_pixel_put(x, y, final_color, im);
}
