/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:07:08 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 20:01:18 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			cylinder_data1(t_rtv1 *im, int count, char **str1)
{
	char		**str2;

	im->object[count].cylinder = (t_cylinder*)malloc(sizeof(t_cylinder));
	str2 = ft_strsplit(str1[1], ' ');
	im->object[count].cylinder->origin =
		init_vect(atof(str2[0]), atof(str2[1]), atof(str2[2]));
	freemass(str2, 3);
	im->object[count].cylinder->diameter = atof(str1[2]);
	str2 = ft_strsplit(str1[3], ' ');
	im->object[count].cylinder->normal =
		normalize(init_vect(atof(str2[0]), atof(str2[1]), atof(str2[2])));
	freemass(str2, 3);
	im->object[count].color =
		init_color(((int)(atof(str1[4])) & 0xFF0000) >> 16,
		((int)(atof(str1[4])) & 0x00FF00) >> 8,
		((int)(atof(str1[4])) & 0x0000FF));
	freemass(str1, 5);
}

void			cylinder_data(t_rtv1 *im, char *scene, int count)
{
	char		**str;
	char		**str1;
	int			i;

	im->object[count].obj_name = "cylinder";
	str = ft_strsplit(scene, '|');
	i = -1;
	str1 = (char**)malloc(sizeof(char*) * 5);
	while (++i < 5)
		str1[i] = ft_strtrim(str[i]);
	freemass(str, 5);
	cylinder_data1(im, count, str1);
}

void			cone_data1(t_rtv1 *im, int count, char **str1)
{
	char		**str2;

	im->object[count].cone = (t_cone*)malloc(sizeof(t_cone));
	str2 = ft_strsplit(str1[1], ' ');
	im->object[count].cone->origin =
		init_vect(atof(str2[0]), atof(str2[1]), atof(str2[2]));
	freemass(str2, 3);
	im->object[count].cone->angle = atof(str1[2]);
	str2 = ft_strsplit(str1[3], ' ');
	im->object[count].cone->normal =
		normalize(init_vect(atof(str2[0]), atof(str2[1]), atof(str2[2])));
	freemass(str2, 3);
	im->object[count].color =
		init_color(((int)(atof(str1[4])) & 0xFF0000) >> 16,
		((int)(atof(str1[4])) & 0x00FF00) >> 8,
		((int)(atof(str1[4])) & 0x0000FF));
	freemass(str1, 5);
}

void			cone_data(t_rtv1 *im, char *scene, int count)
{
	char		**str;
	char		**str1;
	int			i;

	im->object[count].obj_name = "cone";
	str = ft_strsplit(scene, '|');
	i = -1;
	str1 = (char**)malloc(sizeof(char*) * 5);
	while (++i < 5)
		str1[i] = ft_strtrim(str[i]);
	freemass(str, 5);
	cone_data1(im, count, str1);
}
