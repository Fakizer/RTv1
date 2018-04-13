/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 14:15:02 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 20:46:00 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			search_ip(t_rtv1 *im, int x, int y)
{
	if (im->inter->index_of_wo > -1)
	{
		if (im->inter->inters[im->inter->index_of_wo] > 1e-6)
		{
			im->inter->int_pos = vectadd(im->cam->ray->origin,
					vectmult(im->cam->ray->direction,
						im->inter->inters[im->inter->index_of_wo]));
			prelst(im, x, y);
		}
	}
}

void			rtv1_create(t_rtv1 *im)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	init_gxgygz(im);
	init_cwcucv(im->cam, im->xyz);
	while (x < im->width)
	{
		y = 0;
		while (y < im->height)
		{
			init_xyamnt(im, x, y);
			init_cam_ray(im->cam, im);
			free(im->xyamnt);
			check_inter(im);
			search_ip(im, x, y);
			free(im->cam->ray);
			free(im->inter->inters);
			free(im->inter);
			y++;
		}
		x++;
	}
}

int				expose_hook(t_rtv1 *im)
{
	if ((im->rtv = mlx_new_image(im->mlx, im->width, im->height)) == NULL)
		init_error(ERROR_MLX);
	im->rtv_data = mlx_get_data_addr(im->rtv, &im->bpp,
		&im->size_line, &im->end);
	rtv1_create(im);
	mlx_put_image_to_window(im->mlx, im->win, im->rtv, 0, 0);
	mlx_destroy_image(im->mlx, im->rtv);
	return (0);
}

int				key_hook(int keycode, t_rtv1 *im)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(im->mlx, im->win);
		exit(EXIT_OK);
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_rtv1	*im;

	if (ac != 2)
		init_error("I don't see demo!!!");
	check_scene_file(av[1]);
	if ((im = init_rtv1(av[1])) == NULL)
		init_error("");
	parcing_scene(im);
	if ((im->mlx = mlx_init()) == NULL)
		init_error(ERROR_MLX);
	if ((im->win = mlx_new_window(im->mlx, im->width,
		im->height, im->screen_name)) == NULL)
		init_error(ERROR_MLX);
	mlx_key_hook(im->win, key_hook, im);
	mlx_expose_hook(im->win, expose_hook, im);
	mlx_loop(im->mlx);
}
