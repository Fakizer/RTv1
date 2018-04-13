/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_file2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 11:51:01 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 21:18:55 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		check_cone(char **str)
{
	check_dot(str, 1);
	check_sp_pa(str, 0);
	check_dot(str, 3);
	check_color(str);
}

void		check_plane(char **str)
{
	check_dot(str, 1);
	check_pointer(str, 2);
	check_dot(str, 3);
	check_color(str);
}

void		check_sphere(char **str)
{
	check_dot(str, 1);
	check_sp_pa(str, 0);
	check_pointer(str, 3);
	check_color(str);
}

void		check_light(char **str)
{
	check_dot(str, 1);
	check_sp_pa(str, 'y');
	check_pointer(str, 3);
	check_pointer(str, 4);
}

void		check_camera(char **str)
{
	check_dot(str, 1);
	check_pointer(str, 2);
	check_dot(str, 3);
	check_pointer(str, 4);
}
