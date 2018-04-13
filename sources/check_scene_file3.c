/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_file3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 11:51:55 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 22:00:32 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		check_color(char **str)
{
	char *str1;

	if (!(str[4]))
		init_error("invalid demo");
	str1 = ft_strtrim(str[4]);
	if (str1[0] != '0' || str1[1] != 'x')
		init_error("invalid demo");
	check_color1(str1);
	free(str1);
}

void		check_sp_pa(char **str1, int k)
{
	int		i;
	char	*str;

	i = 0;
	if (!(str1[2]))
		init_error("invalid demo");
	else if (k == 'y')
	{
		str = ft_strtrim(str1[2]);
		if (str[0] != '0' || str[1] != '.' || str[2] != '9' ||
			(str[3] < '0' && str[3] > '9'))
			init_error("invalid demo");
		free(str);
	}
	else
		check_sp_pa1(str1);
}

void		check_pointer(char **str, int i)
{
	char *str1;

	if (!(str[i]))
		init_error("invalid demo");
	str1 = ft_strtrim(str[i]);
	if (!(ft_strstr(str1, "*")))
		init_error("invalid demo");
	free(str1);
}

void		check_dot(char **str, int k)
{
	char	*str1;
	char	**str2;
	int		i;
	int		j;

	str1 = ft_strtrim(str[k]);
	str2 = ft_strsplit(str1, ' ');
	free(str1);
	j = -1;
	while (str2[++j] && j < 3)
	{
		i = 0;
		while (str2[j][i] && str2[j][i] != '\0')
		{
			if (str2[j][i] == '-' && (str2[j][i + 1]) != '\0')
				i++;
			if (str2[j][i] < 48 || str2[j][i] > 57)
				init_error("invalid demo");
			i++;
		}
	}
	freemass(str2, 3);
}

void		check_cylinder(char **str)
{
	check_dot(str, 1);
	check_sp_pa(str, 0);
	check_dot(str, 3);
	check_color(str);
}
