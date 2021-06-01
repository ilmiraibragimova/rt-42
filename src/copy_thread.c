/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 22:10:28 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/10 12:21:52 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	thread_copy2(t_rt *r, t_rt *copy)
{
	copy->blur = r->blur;
	copy->stereoscopy = r->stereoscopy;
	copy->stereo = r->stereo;
	copy->menu = r->menu;
	copy->d1 = r->d1;
	copy->i_thr = r->i_thr;
	copy->j_thr = r->j_thr;
	copy->per_data.y_per = r->per_data.y_per;
	copy->per_data.x_per = r->per_data.x_per;
	copy->per_data.z_per = r->per_data.z_per;
	if (!(copy->ray = (t_raydata*)malloc(sizeof(t_raydata))))
	{
		ft_clean(r);
		exit(0);
	}
}

void	thread_copy1(t_rt *r, int count, t_rt *copy)
{
	copy->x = r->x;
	copy->y = r->y;
	copy->i = r->i;
	copy->shadow_t = r->shadow_t;
	copy->color = r->color;
	copy->shad_trans = r->shad_trans;
	copy->light = r->light;
	copy->intensity = r->intensity;
	copy->curent_thread = count;
	copy->win = r->win;
	copy->ren = r->ren;
	copy->screen = r->screen;
	copy->texture = r->texture;
	copy->cam.point = r->cam.point;
	copy->filter = r->filter;
	thread_copy2(r, copy);
}

t_rt	*thread_copy(t_rt *r, int count)
{
	t_rt	*copy;

	if (!(copy = (t_rt *)malloc(sizeof(t_rt))))
	{
		ft_clean(r);
		exit(0);
	}
	copy->cam = r->cam;
	copy->clos = r->clos;
	copy->closest_t = r->closest_t;
	copy->amount_obj = r->amount_obj;
	copy->amount_ligth = r->amount_ligth;
	if (!(copy->obj = (t_obj*)malloc(sizeof(t_obj) * r->amount_obj)))
	{
		ft_clean(r);
		exit(0);
	}
	ft_memcpy(copy->obj, r->obj, sizeof(t_obj) * r->amount_obj);
	thread_copy1(r, count, copy);
	return (copy);
}
