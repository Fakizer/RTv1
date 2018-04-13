/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 18:27:35 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 22:12:04 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		sl_tl_check(int fd)
{
	char *scene;

	get_next_line(fd, &scene);
	if (!(ft_strstr(scene, "|")) && !(ft_strstr(scene, "-------")))
		init_error("invalid demo");
	free(scene);
	get_next_line(fd, &scene);
	if (!(ft_strstr(scene, "objects")))
		init_error("invalid demo");
	else
		tl_check(scene, fd);
}

void		sl_check1(char **str1, int fd)
{
	int		j;
	int		i;
	char	*str;

	j = 1;
	while (++j < 4)
	{
		str = ft_strtrim(str1[j]);
		if (!(str))
			init_error("invalid demo");
		i = -1;
		while (str[++i] != '\0')
		{
			if (str[i] < 48 && str[i] > 57)
				init_error("invalid demo");
		}
		free(str);
	}
	freemass(str1, 5);
	sl_tl_check(fd);
}

void		sl_check(char *scene, int fd)
{
	char **str;

	str = ft_strsplit(scene, '|');
	free(scene);
	if (!(str[1]) || !(ft_strstr(str[1], "RTv1")))
		init_error("invalid demo");
	sl_check1(str, fd);
}

void		fl_check(char *scene, int fd)
{
	char **str;

	str = ft_strsplit(scene, '|');
	free(scene);
	if (!(str[0]) || !(ft_strstr(str[0], "window")))
		init_error("invalid demo");
	if (!(str[1]) || !(ft_strstr(str[1], "name")))
		init_error("invalid demo");
	if (!(str[2]) || !(ft_strstr(str[2], "width")))
		init_error("invalid demo");
	if (!(str[3]) || !(ft_strstr(str[3], "height")))
		init_error("invalid demo");
	freemass(str, 5);
	get_next_line(fd, &scene);
	if (!(ft_strstr(scene, "|")) && !(ft_strstr(scene, "-------")))
		init_error("invalid demo");
	free(scene);
	get_next_line(fd, &scene);
	if (!(ft_strstr(scene, "RTv1")))
		init_error("invalid demo");
	else
		sl_check(scene, fd);
}

void		check_scene_file(char *av)
{
	char		*scene;
	int			fd;

	fd = open(av, O_RDONLY);
	get_next_line(fd, &scene);
	if (!(ft_strstr(scene, "|")) && !(ft_strstr(scene, "-------")))
		init_error("invalid demo");
	free(scene);
	get_next_line(fd, &scene);
	if (!(ft_strstr(scene, "window")))
		init_error("invalid demo");
	else
		fl_check(scene, fd);
	close(fd);
}
