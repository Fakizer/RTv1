/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parc1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:05:13 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 20:01:21 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			plane_data1(t_rtv1 *im, int count, char **str1)
{
	char		**str2;

	im->object[count].plane = (t_plane*)malloc(sizeof(t_plane));
	str2 = ft_strsplit(str1[1], ' ');
	im->object[count].plane->origin =
		init_vect(atof(str2[0]), atof(str2[1]), atof(str2[2]));
	freemass(str2, 3);
	str2 = ft_strsplit(str1[3], ' ');
	im->object[count].plane->normal =
		normalize(init_vect(atof(str2[0]), atof(str2[1]), atof(str2[2])));
	freemass(str2, 3);
	im->object[count].color =
		init_color(((int)(atof(str1[4])) & 0xFF0000) >> 16,
		((int)(atof(str1[4])) & 0x00FF00) >> 8,
		((int)(atof(str1[4])) & 0x0000FF));
	freemass(str1, 5);
}

void			plane_data(t_rtv1 *im, char *scene, int count)
{
	char		**str;
	char		**str1;
	int			i;

	im->object[count].obj_name = "plane";
	str = ft_strsplit(scene, '|');
	i = -1;
	str1 = (char**)malloc(sizeof(char*) * 5);
	while (++i < 5)
		str1[i] = ft_strtrim(str[i]);
	freemass(str, 5);
	plane_data1(im, count, str1);
}

void			sphere_data(t_rtv1 *im, char *scene, int count)
{
	char		**str;
	char		**str2;
	char		**str1;
	int			i;

	im->object[count].sphere = (t_sphere*)malloc(sizeof(t_sphere));
	im->object[count].obj_name = "sphere";
	str = ft_strsplit(scene, '|');
	i = -1;
	str1 = (char**)malloc(sizeof(char*) * 5);
	while (++i < 5)
		str1[i] = ft_strtrim(str[i]);
	freemass(str, 5);
	str2 = ft_strsplit(str1[1], ' ');
	im->object[count].sphere->origin =
		init_vect(atof(str2[0]), atof(str2[1]), atof(str2[2]));
	freemass(str2, 3);
	im->object[count].sphere->diameter = atof(str1[2]);
	im->object[count].color =
		init_color(((int)(atof(str1[4])) & 0xFF0000) >> 16,
		((int)(atof(str1[4])) & 0x00FF00) >> 8,
		((int)(atof(str1[4])) & 0x0000FF));
	freemass(str1, 5);
}

void			light_data(t_rtv1 *im, char *scene, int count)
{
	char		**str;
	char		*str1;
	char		**str2;

	str = ft_strsplit(scene, '|');
	str1 = ft_strtrim(str[1]);
	str2 = ft_strsplit(str1, ' ');
	im->light[count].position.x = atof(str2[0]);
	im->light[count].position.y = atof(str2[1]);
	im->light[count].position.z = atof(str2[2]);
	im->light[count].bl = atof(str[2]);
	freemass(str, 5);
	freemass(str2, 3);
	free(str1);
}

void			camera_data(t_rtv1 *im, char *scene)
{
	char		**str;
	char		**str1;
	char		**str2;
	int			i;

	str = ft_strsplit(scene, '|');
	i = -1;
	str1 = (char**)malloc(sizeof(char*) * 5);
	while (++i < 5)
		str1[i] = ft_strtrim(str[i]);
	freemass(str, 5);
	im->cam = (t_camera*)malloc(sizeof(t_camera));
	str2 = ft_strsplit(str1[1], ' ');
	im->cam->origin = init_vect(atof(str2[0]), atof(str2[1]),
		atof(str2[2]));
	freemass(str2, 3);
	im->cam->cam_step = atof(str1[2]);
	str2 = ft_strsplit(str1[3], ' ');
	im->cam->look_at = init_vect(atof(str2[0]), atof(str2[1]),
		atof(str2[2]));
	freemass(str2, 3);
	freemass(str1, 5);
}
