/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:49:20 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/10 16:24:12 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		closest_func(t_rt *r, t_raydata vew, double t_max, int f)
{
	int i;

	i = r->i;
	if (ft_strequ(r->obj[i].name, "sphere"))
		r->obj[i].t = ray_sphere(vew, r->obj[i], f);
	else if (ft_strequ(r->obj[i].name, "plane"))
		r->obj[i].t = ft_ray_plane(vew, r->obj[i], f);
	else if (ft_strequ(r->obj[i].name, "cone"))
		r->obj[i].t = ft_intersect_ray_cone(&r->obj[i], &vew);
	else if ((ft_strequ(r->obj[i].name, "cylinder")))
		r->obj[i].t = intersect_ray_cylinder(&r->obj[i], &vew);
	else if (ft_strequ(r->obj[i].name, "torus"))
		r->obj[i].t = ft_ray_torus(&vew, &r->obj[i], f);
	else if (ft_strequ(r->obj[i].name, "paraboloid"))
		r->obj[i].t = ft_paraboloid_inter(&vew, &r->obj[i]);
	else if (ft_strequ(r->obj[i].name, "cube"))
		r->obj[i].t = ft_cube_ray(&vew, &r->obj[i], f);
	if (r->obj[i].t >= 0.00001 && r->obj[i].t <= t_max &&\
		r->obj[i].t < r->closest_t)
	{
		r->closest_t = r->obj[i].t;
		r->clos = i;
	}
	return (r->closest_t);
}

t_vec		ft_traceray(t_raydata *ray, t_rt *r, int f, int depth)
{
	t_vec	s1;

	r->i = -1;
	s1 = (t_vec) {0, 0, 0};
	r->closest_t = INFINITY;
	r->clos = -1;
	while (++(r->i) < r->amount_obj)
		r->closest_t = closest_func(r, *ray, INFINITY, f);
	if (r->clos == -1)
		return (s1);
	r->obj[r->clos].color1 = ft_lighting1(r, *ray, depth);
	if (r->filter)
		effects(r);
	r->obj[r->clos].color1.x = r->obj[r->clos].color1.x > 255 ?\
	255 : r->obj[r->clos].color1.x;
	r->obj[r->clos].color1.y = r->obj[r->clos].color1.y > 255 ?\
	255 : r->obj[r->clos].color1.y;
	r->obj[r->clos].color1.z = r->obj[r->clos].color1.z > 255 ?\
	255 : r->obj[r->clos].color1.z;
	return (r->obj[r->clos].color1);
}

t_raydata	*creat_ray(double max_len, t_vec point, t_vec direction, t_rt *r)
{
	r->ray->t_max = max_len;
	r->ray->point = point;
	r->ray->direction = direction;
	return (r->ray);
}

void		ft_render(t_rt *r)
{
	t_vec	color;
	int		color1;

	SDL_LockSurface(r->screen);
	r->cam.roter = matr_rot(r->cam);
	r->j_thr = (HEIGHT / 2) - (HEIGHT / N_THRED) * r->curent_thread;
	while (r->j_thr > HEIGHT / 2 - ((HEIGHT / N_THRED)\
	* (r->curent_thread + 1)))
	{
		r->i_thr = -(WIDTH / 2) - 1;
		while (++(r->i_thr) <= WIDTH / 2)
		{
			r->d1 = (t_vec) {r->i_thr * 1.0 / WIDTH, \
			r->j_thr * 1.0 / WIDTH, DIST};
			r->d1 = vec_norm(rot(r->d1, r->cam.roter));
			r->ray = creat_ray(INFINITY, r->cam.point, r->d1, r);
			color = ft_traceray(r->ray, r, 0, 5);
			color1 = SDL_MapRGB(r->screen->format, (int)(color.x), \
			(int)(color.y), (int)(color.z));
			((int *)(r->screen->pixels))[(WIDTH / 2 + r->i_thr) + \
			(HEIGHT / 2 - r->j_thr) * WIDTH] = color1;
		}
		r->j_thr--;
	}
	SDL_UnlockSurface(r->screen);
}
