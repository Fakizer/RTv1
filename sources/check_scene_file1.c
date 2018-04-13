/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_file1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 11:49:00 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 22:31:01 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		freemass(char **data, int k)
{
	int j;

	j = 0;
	while (j < k)
	{
		free(data[j]);
		j++;
	}
	free(data);
}

void		data_check(char *scene)
{
	char **str;

	str = ft_strsplit(scene, '|');
	if ((str[0]) && (ft_strstr(str[0], "camera")))
		check_camera(str);
	if ((str[0]) && (ft_strstr(str[0], "light")))
		check_light(str);
	if ((str[0]) && (ft_strstr(str[0], "sphere")))
		check_sphere(str);
	if ((str[0]) && (ft_strstr(str[0], "plane")))
		check_plane(str);
	if ((str[0]) && (ft_strstr(str[0], "cone")))
		check_cone(str);
	if ((str[0]) && (ft_strstr(str[0], "cylinder")))
		check_cylinder(str);
	freemass(str, 6);
}

int			check_end(int fd, int *clo)
{
	int		ret;
	char	*scene;

	if (clo[0] == 0 && clo[1] == 0 && clo[2] == 0)
		init_error("invalid demo");
	ret = get_next_line(fd, &scene);
	free(scene);
	if (ret == 0)
		return (1);
	ret = get_next_line(fd, &scene);
	free(scene);
	if (ret == 0)
		init_error("invalid demo");
	return (0);
}

void		object_check(int fd, int *clo)
{
	int		ret;
	char	*scene;

	while ((ret = get_next_line(fd, &scene)) > 0)
	{
		if (ft_strstr(scene, "camera"))
			clo[0] = 1;
		if (ft_strstr(scene, "light"))
			clo[1] = 1;
		if ((ft_strstr(scene, "sphere")) || (ft_strstr(scene, "plane")) ||
			(ft_strstr(scene, "cone")) || (ft_strstr(scene, "cylinder")))
			clo[2] = 1;
		if ((ft_strstr(scene, "|")) && (ft_strstr(scene, "-------")))
		{
			free(scene);
			if (check_end(fd, clo))
				break ;
		}
		if (clo[0] == 1 || clo[1] == 1 || clo[2] == 1)
			data_check(scene);
		free(scene);
	}
	if (clo[0] == 0 || clo[1] == 0 || clo[2] == 0)
		init_error("invalid demo");
}

void		tl_check(char *scene, int fd)
{
	char **str;

	str = ft_strsplit(scene, '|');
	free(scene);
	if (!(str[0]) || !(ft_strstr(str[0], "objects")))
		init_error("invalid demo");
	if (!(str[1]) || !(ft_strstr(str[1], "origin")))
		init_error("invalid demo");
	if (!(str[2]) || !(ft_strstr(str[2], "spec param")))
		init_error("invalid demo");
	tl_check1(str, fd);
}
