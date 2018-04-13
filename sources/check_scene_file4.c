/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_file4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 12:37:59 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 21:58:56 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		check_color1(char *str)
{
	int i;

	i = 2;
	while (i < 6)
	{
		if (!(str[i]) || (str[i] < 48 && str[i] > 57))
			init_error("invalid demo");
		if (!(str[i]) || (str[i] < 65 && str[i] > 70))
			init_error("invalid demo");
		i++;
	}
}

void		check_sp_pa1(char **str1)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strtrim(str1[2]);
	while (str[i] && str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			init_error("invalid demo");
		i++;
	}
	free(str);
}

void		tl_check1(char **str, int fd)
{
	char	*scene;
	int		clo[3];

	clo[0] = 0;
	clo[1] = 0;
	clo[2] = 0;
	if (!(str[3]) || !(ft_strstr(str[3], "rot_c_c")))
		init_error("invalid demo");
	if (!(str[4]) || !(ft_strstr(str[4], "color")))
		init_error("invalid demo");
	freemass(str, 5);
	get_next_line(fd, &scene);
	if (!(ft_strstr(scene, "|")) && !(ft_strstr(scene, "-------")))
		init_error("invalid demo");
	free(scene);
	object_check(fd, clo);
}
