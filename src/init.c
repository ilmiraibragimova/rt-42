/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:19:21 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/11 14:38:55 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init(t_rt *r)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0 && TTF_Init() >= 0)
		if ((r->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,\
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
			if ((r->ren = SDL_CreateRenderer(r->win, -1,\
			SDL_RENDERER_SOFTWARE)))
				if ((r->screen = SDL_GetWindowSurface(r->win)))
					return ;
	ft_putendl(SDL_GetError());
	ft_clean(r);
	exit(1);
}

void	ft_init_cam(t_rt *r)
{
	r->cam.point = (t_vec){0, 0, 0};
	r->cam.angles = (t_vec){0, 0, 0};
	r->cam.direct = (t_vec){0, 0, 0};
	r->cam.roter.vec = (t_vec){0, 0, 0};
	r->cam.roter.l = 0;
}

void	init_r_second(t_rt *r)
{
	r->filter = 0;
	r->blur = 0;
	r->stereoscopy = 0;
	r->stereo = 0;
	r->x = 0;
	r->y = 0;
	r->d1 = (t_vec){0, 0, 0};
	r->d = 0;
	r->clos = 0;
	r->i = 0;
	r->shadow_t = 0;
	r->closest_t = 0;
	r->intensity = 0;
	r->color = (t_vec){0, 0, 0};
	r->pixels = NULL;
	r->shad_trans = 0;
	r->menu = 0;
	r->curent_thread = 0;
	r->ray = NULL;
	ft_init_cam(r);
}

void	init_r(t_rt *r)
{
	r->count = 0;
	r->amount_obj = 0;
	r->amount_ligth = 0;
	r->l = 0;
	r->j_thr = 0;
	r->i_thr = 0;
	r->texture = NULL;
	r->screen = NULL;
	r->ren = NULL;
	r->win = NULL;
	r->light = NULL;
	r->obj = NULL;
	r->per_data.x_per = 0;
	r->per_data.y_per = 0;
	r->per_data.z_per = 0;
	init_r_second(r);
}
