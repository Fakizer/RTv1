/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 16:37:38 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 15:12:44 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_error(char *pref)
{
	ft_putstr_fd(PROG_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(pref, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}
