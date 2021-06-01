/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:19:21 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/26 17:26:19 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	for_blur(t_rt *r)
{
	r->d1 = (t_vec) {r->i_thr * 1.0 / WIDTH, \
	r->j_thr * 1.0 / WIDTH, DIST};
	r->d1 = vec_norm(rot(r->d1, r->cam.roter));
	r->ray = creat_ray(INFINITY, r->cam.point, r->d1, r);
}

void	blur(t_rt *r)
{
	t_vec	color;
	t_vec	color1;
	int		color2;
	int		i;

	i = 0;
	r->cam.point.x -= 0.05;
	while (i < 10)
	{
		for_blur(r);
		color = ft_traceray(r->ray, r, 0, 5);
		color1 = (i == 0) ? color : color1;
		color1.x = (color1.x + color.x) / 2;
		color1.y = (color1.y + color.y) / 2;
		color1.z = (color1.z + color.z) / 2;
		r->cam.point.x += 0.01;
		i++;
	}
	color2 = SDL_MapRGB(r->screen->format, (int)(color1.x), \
	(int)(color1.y), (int)(color1.z));
	((int *)(r->screen->pixels))[(WIDTH / 2 + r->i_thr) + \
	(HEIGHT / 2 - r->j_thr) * WIDTH] = color2;
	r->cam.point.x = r->cam.point.x - 0.01 * i / 2;
}

void	ft_blur(t_rt *r)
{
	SDL_LockSurface(r->screen);
	r->cam.roter = matr_rot(r->cam);
	r->j_thr = (HEIGHT / 2) - (HEIGHT / N_THRED) * r->curent_thread;
	while (r->j_thr > HEIGHT / 2 - ((HEIGHT / N_THRED)\
	* (r->curent_thread + 1)))
	{
		r->i_thr = -(WIDTH / 2) - 1;
		while (++(r->i_thr) <= WIDTH / 2)
			blur(r);
		r->j_thr--;
	}
	SDL_UnlockSurface(r->screen);
}
