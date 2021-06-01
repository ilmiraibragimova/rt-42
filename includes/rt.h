/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 00:18:42 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/11 14:14:17 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RT_H
# define RT_RT_H
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "veclib.h"
# include <SDL2/SDL.h>
# include "../json-c/json.h"
# include "../frameworks/SDL2.framework/Headers/SDL_surface.h"
# include "../frameworks/SDL2.framework/Headers/SDL_video.h"
# include "../frameworks/SDL2.framework/Headers/SDL_render.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# define WIDTH 800
# define HEIGHT 600
# define DIST 1
# define N_THRED 4

typedef struct	s_board
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	z1;
	double	z2;
}				t_board;

typedef struct	s_screenshot
{
	SDL_Renderer	*ren;
	SDL_Surface		*surface;
	char			*name;
	SDL_Rect		win_size;
}				t_screenshot;

typedef struct	s_matr
{
	double			l;
	t_vec			vec;
}				t_matr;

typedef struct	s_vector
{
	t_vec			point;
	t_vec			direct;
	t_vec			angles;
	t_matr			roter;
}				t_vector;

typedef struct	s_vecs
{
	t_vec	l;
	t_vec	k;
	double	t_max;
}				t_vecs;

typedef struct	s_perl
{
	double	x_per;
	double	y_per;
	double	z_per;
}				t_perl;

typedef struct	s_t
{
	SDL_Surface		*img;
	SDL_PixelFormat	*format;
	char			*pixels;
	int				bytes_per_pixel;
	int				l_size;
	int				size;
	int				width;
	int				height;
	Uint32			rmask;
	Uint32			rshift;
	Uint32			rloss;
	Uint32			gmask;
	Uint32			gshift;
	Uint32			gloss;
	Uint32			bmask;
	Uint32			bshift;
	Uint32			bloss;
}				t_t;

typedef struct	s_obj
{
	double	radius;
	t_vec	center;
	t_vec	rot;
	t_vec	color;
	t_vec	n;
	t_vec	limit;
	double	specular;
	double	reflect;
	double	transperency;
	char	*name;
	double	t;
	t_vec	p;
	t_vec	color1;
	double	in;
	double	out;
	double	scale2;
	double	max;
	double	min;
	int		flag_tex;
	int		t_w;
	int		t_h;
	int		t_col;
	double	shad;
	int		is_limit;
	double	limit1;
	t_t		*tex;
	int		path;
}				t_obj;

typedef struct	s_raydata
{
	double		t_max;
	t_vec		direction;
	t_vec		st_cent;
	t_vec		point;
}				t_raydata;

typedef struct	s_light
{
	char			*type;
	double			intensity;
	t_vec			position;
	t_vec			direction;
}				t_light;

typedef struct	s_textr
{
	double	h;
	double	w;
	t_vec	color_a;
	t_vec	color_b;
}				t_textr;

typedef struct	s_rt
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*screen;
	SDL_Texture		*texture;
	int				x;
	int				y;
	int				d;
	t_vec			d1;
	t_vector		cam;
	t_obj			*obj;
	t_light			*light;
	int				count;
	int				clos;
	int				amount_ligth;
	int				i;
	int				l;
	double			shadow_t;
	double			closest_t;
	int				amount_obj;
	double			intensity;
	int				curent_thread;
	int				i_thr;
	int				j_thr;
	t_vec			*pixels;
	t_vec			color;
	t_raydata		*ray;
	int				filter;
	int				blur;
	int				stereo;
	int				stereoscopy;
	int				menu;
	double			shad_trans;
	t_perl			per_data;
}				t_rt;

typedef struct	s_equl
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			m;
	double			n;
	double			p;
	double			o;
	double			tmp;
	double			d1;
	double			d2;
}				t_equl;

void			ft_render(t_rt *r);
void			ft_init(t_rt *r);
void			init_r(t_rt *r);
SDL_Color		take_color();
void			take_rect(t_rt *r, int a, int b);
void			take_rect_for_long_menu(t_rt *r);
void			init_r_second(t_rt *r);
void			for_menu(t_rt *r);
void			for_keys(t_rt *r, const uint8_t *keys);
void			rotate_cam(t_rt *r, const uint8_t *keys);
void			key(t_rt *r, const uint8_t *keys);
void			menu_first(t_rt *r, SDL_Color text_color, \
				TTF_Font *verdana_font);
void			menu_second(t_rt *r, SDL_Color text_color, \
				TTF_Font *verdana_font);
void			menu_third(t_rt *r, SDL_Color text_color, \
				TTF_Font *verdana_font);
void			menu_fourth(t_rt *r, SDL_Color text_color, \
				TTF_Font *verdana_font);
t_t				*tex_new_surface(SDL_Surface *s);
Uint32			tex_get_pixel(t_t *tex, int x, int y);
t_t				*tex_new_bmp(t_obj *obj);
t_vec			calculate_texture_color(t_rt *r);
void			ft_parser(char *arg, t_rt *r);
t_vec			ft_lighting1(t_rt *r, t_raydata vew, int depth);
double			ft_ray_plane(t_raydata vew, t_obj obj, int f);
t_vec			ft_norm_sphere(t_vec p, t_rt *r);
double			ray_sphere(t_raydata vew, t_obj obj, int f);
t_vec			ft_norm_plane(t_rt *r);
double			ft_get_t(double k1, double k2, double k3, int f);
t_vec			ft_norm_con(t_vec vew, t_vec p, t_rt *r);
t_vec			ft_norm_cylinder(t_vec vew, t_vec p, t_rt *r);
void			ft_put_error(char *s);
double			closest_func(t_rt *r, t_raydata vew, double t_max, int f);
t_matr			matr_rot(t_vector camera);
t_vec			rot(t_vec vector, t_matr matr);
t_raydata		*creat_ray(double max_len, t_vec point,\
	t_vec direction, t_rt *r);
void			matr_normal(t_matr *m);
int				bord(t_rt *r, t_light *tmp);
void			error_plane(void);
void			error_cone(void);
void			error_cyl(void);
void			error_spere(void);
void			error_open(void);
void			error_lite(void);
void			error_malloc();
void			crazy(t_rt *r);
void			invert(t_rt *r);
void			gray(t_rt *r);
void			sepia(t_rt *r);
void			blur(t_rt *r);
void			stereoscopy(t_rt *r);
t_vec			ft_traceray(t_raydata *ray, t_rt *r, int f, int depth);
t_vec			transperency(t_rt *r, t_raydata ray);
t_vec			pattern_at(t_vec p, t_rt *r, t_vec s);
t_vec			reflect_ray(t_vec r, t_vec n);
double			lighting(t_rt *r, t_vec p, t_raydata vew);
double			noise(double x, double y, double z);
void			ft_json(char *s, t_rt *r);
void			parse_cam(struct json_object *parsed_json, t_rt *r);
void			parse_light(struct json_object *parsed_json,\
				t_rt *r, char *key1);
void			parse_sphere(t_rt *r, struct json_object *parsed_json);
void			parse_cone(t_rt *r, struct json_object *parsed_json);
void			parse_plane(t_rt *r, struct json_object *parsed_json);
void			parse_cylinder(t_rt *r, struct json_object *parsed_json);
void			parse_paraboloid(t_rt *r, struct json_object *parsed_json);
t_vec			ft_paraboloid_norm(t_obj *parab);
double			ft_paraboloid_inter(t_raydata *ray, t_obj *parab);
int				ft_equation_3(double *x, double a, double b, double c);
int				ft_equation_4(t_equl equl, double *x);
void			parse_torus(t_rt *r, struct json_object *parsed_json);
double			ft_ray_torus(t_raydata *ray, t_obj *t, int f);
t_vec			ft_norm_torus(t_obj *t);
void			error_parab(void);
void			error_tore(void);
t_vec			ray_trans(t_vec ray_dir, t_vec normal, double mat_ref);
void			ft_json_tex(t_rt *r, struct json_object *parsed_json,\
	char *key);
double			ft_equation(t_equl equl, int f);
char			*find_path_third(int p);
char			*find_path_second(int p);
double			ft_cube_ray(t_raydata *ray, t_obj *c, int f);
void			pattern_at_f(t_textr *texture_map, t_rt *r);
t_vec			norm_cube(t_rt *r);
void			parse_cube(t_rt *r, struct json_object *parsed_json);
void			threads(t_rt *r);
int				screenshot(t_rt *r);
double			*spherical_map(t_vec p, t_rt *r, double u_v[]);
void			ft_sort(double *x);
double			check_intersect(t_vec *ray, t_vec *pos,\
	t_vec *axis, double len);
void			solve_quadratic_equation(t_equl *discr);
void			effects(t_rt *r);
double			ft_intersect_ray_cone(t_obj *cone, t_raydata *ray);
double			intersect_ray_cylinder(t_obj *tube, t_raydata *ray);
void			check_cone(t_obj *cone);
void			check_cylinder(t_obj *cyl);
void			check_parab(t_obj *plane);
void			check_plane(t_obj *plane);
void			check_sphere(t_obj *sphere);
void			check_torus(t_obj *plane);
void			ft_blur(t_rt *r);
void			ft_stereoscopy(t_rt *r);
t_rt			*ft_clean(t_rt *r);
void			init_perandom5(int perandom[]);
void			init_perandom(int perandom[]);
void			init_perandom10(int perandom[]);
void			init_perlin (int perlin[]);
t_rt			*thread_copy(t_rt *r, int count);
double			ft_shadow(t_rt *r, t_vec p, t_vecs pos);
double			ft_shadow1(t_rt *r, t_raydata *ray, t_vecs pos, int i);
void			error_read(void);
double			ft_dist(t_equl t, t_raydata *ray, t_obj *obj);
int				ft_is_limit(t_raydata *ray, t_equl t, t_obj *cyl);
void			menu(t_rt *r);
char			*find_path(int p);
t_vec			rotate_vec(t_vec angle, t_vec a);
#endif
