/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvlasenk <vvlasenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/01 18:59:33 by vvlasenk          #+#    #+#             */
/*   Updated: 2017/10/19 19:48:02 by vvlasenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# define PROG_NAME			"RTv1"
# define ERROR_EXIT			1
# define ERROR				-1
# define ERROR_PROC			"error while reading file"
# define EMPTYFILE			"error: the file is empty"
# define ERROR_MLX			"minilibx error occured"
# define EXIT_OK			0
# define ERROR_END			0
# define MY_LITTLE_END		0
# define MY_BIG_END			1

typedef unsigned char		t_tsvet;

typedef enum				e_bool
{
	FT_FALSE,
	FT_TRUE
}							t_bool;

typedef enum				e_key
{
	ESC = 53,
	F1 = 122,
	ZOOM_UP = 4,
	ZOOM_DOWN = 5,
	HOME = 115,
	LEFT_MOUSE = 1,
	RIGHT_MOUSE = 2,
	A = 0,
	S = 1,
	D = 2,
	W = 13,
}							t_key;

typedef struct				s_color
{
	t_tsvet					r;
	t_tsvet					g;
	t_tsvet					b;
}							t_color;

typedef struct				s_vect
{
	double					x;
	double					y;
	double					z;
}							t_vect;

typedef struct				s_light
{
	t_vect					position;
	double					bl;
}							t_light;

typedef struct				s_ray
{
	t_vect					origin;
	t_vect					direction;
}							t_ray;

typedef struct				s_cylinder
{
	t_vect					origin;
	t_vect					normal;
	double					diameter;
	double					t;
}							t_cylinder;

typedef struct				s_cone
{
	t_vect					origin;
	t_vect					normal;
	double					angle;
	double					t;
}							t_cone;

typedef struct				s_plane
{
	t_vect					origin;
	t_vect					normal;
	double					t;
}							t_plane;

typedef struct				s_sphere
{
	t_vect					origin;
	double					diameter;
	double					t;
}							t_sphere;

typedef struct				s_cwcucv
{
	t_vect					cw;
	t_vect					cu;
	t_vect					cv;
}							t_wuv;

typedef struct				s_camera
{
	t_vect					origin;
	t_vect					look_at;
	double					cam_step;
	t_wuv					*wuv;
	t_ray					*ray;
}							t_camera;

typedef struct				s_object
{
	char					*obj_name;
	t_vect					normal;
	t_color					color;
	t_sphere				*sphere;
	t_plane					*plane;
	t_cone					*cone;
	t_cylinder				*cylinder;
}							t_object;

typedef struct				s_gxgygz
{
	t_vect					gx;
	t_vect					gy;
	t_vect					gz;
}							t_xyz;

typedef struct				s_amnt
{
	double					xamnt;
	double					yamnt;
}							t_amnt;

typedef struct				s_inter
{
	double					*inters;
	int						index_of_wo;
	t_vect					int_pos;
}							t_inter;

typedef struct				s_rtv1
{
	void					*mlx;
	void					*win;
	void					*rtv;
	char					*rtv_data;
	char					*screen_name;
	char					*scene_file;
	int						width;
	int						height;
	double					aspectratio;
	int						bpp;
	int						end;
	int						size_line;
	t_camera				*cam;
	t_light					*light;
	int						count_light;
	int						num_light;
	t_object				*object;
	int						count_object;
	int						num_object;
	t_xyz					*xyz;
	t_amnt					*xyamnt;
	t_inter					*inter;
}							t_rtv1;

void						init_error(char *pref);
t_rtv1						*init_rtv1(char *scene);
void						parcing_scene(t_rtv1 *im);
t_object					*count_object(t_rtv1 *im);
t_light						*count_light(t_rtv1 *im);
void						windows_data(int fd, t_rtv1 *im);
void						check_line(char *scene, t_rtv1 *im);
void						plane_data1(t_rtv1 *im, int count, char **str1);
void						plane_data(t_rtv1 *im, char *scene, int count);
void						sphere_data(t_rtv1 *im, char *scene, int count);
void						light_data(t_rtv1 *im, char *scene, int count);
void						camera_data(t_rtv1 *im, char *scene);
void						cylinder_data1(t_rtv1 *im, int count, char **str1);
void						cylinder_data(t_rtv1 *im, char *scene, int count);
void						cone_data1(t_rtv1 *im, int count, char **str1);
void						cone_data(t_rtv1 *im, char *scene, int count);
int							key_hook(int keycode, t_rtv1 *im);
int							expose_hook(t_rtv1 *im);
void						rtv1_create(t_rtv1 *im);
void						search_ip(t_rtv1 *im, int x, int y);
void						prelst(t_rtv1 *im, int x, int y);
void						init_gxgygz(t_rtv1 *im);
void						init_cwcucv(t_camera *cam, t_xyz *xyz);
void						init_xyamnt(t_rtv1 *im, int x, int y);
void						init_cam_ray(t_camera *cam, t_rtv1 *im);
void						check_inter(t_rtv1 *im);
int							win_obj_ind(double *object_int, t_rtv1 *im);
int							win_obj_ind1(double *object_int, t_rtv1 *im);
int							win_obj_ind2(double *object_int, t_rtv1 *im,
	double max);
void						prelst(t_rtv1 *im, int x, int y);
double						sp_pl(t_object *obj, t_ray *ray, int index,
	int ind);
double						co_cy(t_object *obj, t_ray *ray, int index,
	int ind);
t_vect						init_vect(double x, double y, double z);
t_ray						*init_ray(t_vect o, t_vect d);
t_color						init_color(t_tsvet r, t_tsvet g, t_tsvet b);
t_light						*init_light(t_vect p, t_color c);
t_vect						negative(t_vect vect);
t_vect						normalize(t_vect vect);
t_vect						crossproduct(t_vect vect, t_vect v);
t_vect						vectmult(t_vect vect, double scalar);
t_vect						vectadd(t_vect vect, t_vect v);
double						dotproduct(t_vect ray, t_vect normal);
double						magnitude(t_vect vect);
t_color						coloradd(t_color c1, t_color c2);
double						find_int_sp(t_sphere *sphere, t_ray *ray);
double						find_int_pl(t_plane *plane, t_ray *ray);
double						find_int_cyl(t_cylinder *cylinder, t_ray *ray);
double						find_int_co(t_cone *cone, t_ray *ray);
t_color						set_color(t_rtv1 *im, t_object *obj,
	t_light *light, t_ray *ray);
void						img_pixel_put(int x, int y, t_color color,
	t_rtv1 *im);
t_vect						get_normal_sphere(t_vect intersection_position,
	t_vect origin);
t_vect						get_normal_cylinder(t_vect int_pos, t_ray *ray,
	t_cylinder *obj);
t_vect						get_normal_cone(t_vect int_pos, t_ray *ray,
	t_cone *obj);
int							shadow(t_rtv1 *im, t_light *light,
	t_vect intersection_position, int ind);
void						check_scene_file(char	*av);
void						fl_check(char *scene, int fd);
void						sl_check(char *scene, int fd);
void						sl_check1(char **str, int fd);
void						sl_tl_check(int fd);
void						tl_check(char *scene, int fd);
void						object_check(int fd, int *clo);
int							check_end(int fd, int *clo);
void						data_check(char *scene);
void						check_camera(char **str);
void						check_light(char **str);
void						check_sphere(char **str);
void						check_plane(char **str);
void						check_cone(char **str);
void						check_cylinder(char **str);
void						check_dot(char **str, int k);
void						check_pointer(char **str, int i);
void						check_sp_pa(char **str, int k);
void						check_color(char **str);
void						freemass(char **data, int k);
void						tl_check1(char **str, int fd);
void						check_sp_pa1(char **str);
void						check_color1(char *str);

#endif
