/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:27:08 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 21:06:59 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			windows_data(int fd, t_rtv1 *im)
{
	int			ret;
	char		*scene;
	char		**str;
	char		**str1;
	int			i;

	ret = get_next_line(fd, &scene);
	free(scene);
	ret = get_next_line(fd, &scene);
	str = ft_strsplit(scene, '|');
	free(scene);
	i = -1;
	str1 = (char**)malloc(sizeof(char*) * 4);
	while (++i < 4)
		str1[i] = ft_strtrim(str[i]);
	freemass(str, 5);
	im->screen_name = ft_strnew(ft_strlen(str1[1]));
	im->screen_name = ft_strcat(im->screen_name, str1[1]);
	im->width = ft_atoi(str1[2]);
	im->height = ft_atoi(str1[3]);
	im->aspectratio = (double)im->width / (double)im->height;
	freemass(str1, 4);
	if (im->width <= 0 || im->height <= 0)
		init_error("wrong data");
}

t_light			*count_light(t_rtv1 *im)
{
	t_light		*light;
	int			fd;
	char		*scene;
	int			i;

	fd = open(im->scene_file, O_RDONLY);
	while (get_next_line(fd, &scene))
	{
		if (ft_strstr(scene, "light"))
			im->count_light++;
		free(scene);
	}
	close(fd);
	light = (t_light*)malloc(sizeof(t_light) * im->count_light);
	i = -1;
	while (++i < im->count_light)
	{
		light[i].position = init_vect(0, 0, 0);
		light[i].bl = 0;
	}
	return (light);
}

t_object		*count_object(t_rtv1 *im)
{
	t_object	*obj;
	int			fd;
	char		*scene;
	int			i;

	fd = open(im->scene_file, O_RDONLY);
	while (get_next_line(fd, &scene))
	{
		if (ft_strstr(scene, "sphere") || ft_strstr(scene, "plane") ||
			ft_strstr(scene, "cone") || ft_strstr(scene, "cylinder"))
			im->count_object++;
		free(scene);
	}
	close(fd);
	obj = (t_object*)malloc(sizeof(t_object) * im->count_object);
	i = -1;
	while (++i < im->count_object)
		obj[i].obj_name = NULL;
	return (obj);
}

void			check_line(char *scene, t_rtv1 *im)
{
	if (ft_strstr(scene, "camera"))
		camera_data(im, scene);
	if (ft_strstr(scene, "light"))
		light_data(im, scene, im->num_light++);
	if (ft_strstr(scene, "sphere"))
		sphere_data(im, scene, im->num_object++);
	if (ft_strstr(scene, "plane"))
		plane_data(im, scene, im->num_object++);
	if (ft_strstr(scene, "cone"))
		cone_data(im, scene, im->num_object++);
	if (ft_strstr(scene, "cylinder"))
		cylinder_data(im, scene, im->num_object++);
}

void			parcing_scene(t_rtv1 *im)
{
	char		*scene;
	int			ret;
	int			fd;

	im->object = count_object(im);
	im->light = count_light(im);
	fd = open(im->scene_file, O_RDONLY);
	while ((ret = get_next_line(fd, &scene)) > 0)
	{
		if (ft_strstr(scene, "window"))
			windows_data(fd, im);
		check_line(scene, im);
		free(scene);
	}
	free(scene);
	close(fd);
}
