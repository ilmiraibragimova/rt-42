/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:59:11 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/01 20:09:58 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	init_shadow(t_rt *r, t_vec p)
{
	r->shad_trans = 1;
	r->shadow_t = 0;
	p = vec_sum(p, vec_scale(r->obj[r->clos].n, 0.000001));
	return (p);
}

double	ft_shadow_plane(t_rt *r, t_raydata *ray, t_vecs pos, int i)
{
	r->shadow_t = ft_ray_plane(*ray, r->obj[i], 0);
	if (r->shadow_t < pos.t_max && r->shadow_t > 0.0001)
	{
		if (r->obj[i].transperency == 0)
			return (0);
		else if (r->shad_trans > r->obj[i].transperency && r->shadow_t > 0.1)
			r->shad_trans = r->obj[i].transperency;
	}
	return (r->shad_trans);
}

double	ft_shadow_sphere(t_rt *r, t_raydata *ray, t_vecs pos, int i)
{
	r->shadow_t = ray_sphere(*ray, r->obj[i], 0);
	if (r->shadow_t < pos.t_max && r->shadow_t > 0.0001)
	{
		if (r->obj[i].transperency == 0)
			return (0);
		else if (r->shad_trans > r->obj[i].transperency && r->shadow_t > 0.1)
			r->shad_trans = r->obj[i].transperency;
	}
	return (r->shad_trans);
}

double	ft_shadow_cylinder(t_rt *r, t_raydata *ray, t_vecs pos, int i)
{
	r->shadow_t = intersect_ray_cylinder(&r->obj[i], ray);
	if (r->shadow_t < pos.t_max && r->shadow_t > 0.0001)
	{
		if (r->obj[i].transperency == 0)
			return (0);
		else if (r->shad_trans > r->obj[i].transperency && r->shadow_t > 0.1)
			r->shad_trans = r->obj[i].transperency;
	}
	return (r->shad_trans);
}

double	ft_shadow(t_rt *r, t_vec p, t_vecs pos)
{
	int			i;
	t_raydata	*ray;

	i = -1;
	p = init_shadow(r, p);
	ray = creat_ray(pos.t_max, p, vec_norm(pos.l), r);
	while (++i < r->amount_obj)
	{
		if (ft_strequ(r->obj[i].name, "plane") && \
			(!(ft_shadow_plane(r, ray, pos, i))))
			return (0);
		else if (ft_strequ(r->obj[i].name, "sphere") &&\
			(!(ft_shadow_sphere(r, ray, pos, i))))
			return (0);
		else if (ft_strequ(r->obj[i].name, "cylinder") && \
			(!(ft_shadow_cylinder(r, ray, pos, i))))
			return (0);
		else if (ft_shadow1(r, ray, pos, i) == 0)
			return (0);
	}
	return (r->shad_trans);
}
