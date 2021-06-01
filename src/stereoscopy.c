/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereoscopy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 21:28:17 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 22:17:51 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	stereoscopy(t_rt *r)
{
	t_vec	color;
	t_vec	color1;
	int		color2;

	r->cam.point.x = r->cam.point.x - 0.2;
	r->stereo = 0;
	r->d1 = (t_vec) {r->i_thr * 1.0 / WIDTH, \
	r->j_thr * 1.0 / WIDTH, DIST};
	r->d1 = vec_norm(rot(r->d1, r->cam.roter));
	r->ray = creat_ray(INFINITY, r->cam.point, r->d1, r);
	color = ft_traceray(r->ray, r, 0, 5);
	r->cam.point.x = r->cam.point.x + 0.4;
	r->stereo = 1;
	r->d1 = (t_vec) {r->i_thr * 1.0 / WIDTH, \
	r->j_thr * 1.0 / WIDTH, DIST};
	r->d1 = vec_norm(rot(r->d1, r->cam.roter));
	r->ray = creat_ray(INFINITY, r->cam.point, r->d1, r);
	color1 = ft_traceray(r->ray, r, 0, 5);
	color2 = SDL_MapRGB(r->screen->format, (int)(color.x), \
	(int)(color.y + color1.y) / 2, (int)(color1.z));
	((int *)(r->screen->pixels))[(WIDTH / 2 + r->i_thr) + \
	(HEIGHT / 2 - r->j_thr) * WIDTH] = color2;
	r->cam.point.x = r->cam.point.x - 0.2;
}

void	ft_stereoscopy(t_rt *r)
{
	SDL_LockSurface(r->screen);
	r->cam.roter = matr_rot(r->cam);
	r->j_thr = (HEIGHT / 2) - (HEIGHT / N_THRED) * r->curent_thread;
	while (r->j_thr > HEIGHT / 2 - ((HEIGHT / N_THRED)\
	* (r->curent_thread + 1)))
	{
		r->i_thr = -(WIDTH / 2) - 1;
		while (++(r->i_thr) <= WIDTH / 2)
			stereoscopy(r);
		r->j_thr--;
	}
	SDL_UnlockSurface(r->screen);
}
