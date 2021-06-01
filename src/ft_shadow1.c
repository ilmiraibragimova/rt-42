/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 19:31:58 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/02 13:06:39 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_shadow_torus(t_rt *r, t_raydata *ray, t_vecs pos, int i)
{
	r->shadow_t = ft_ray_torus(ray, &r->obj[i], 0);
	if (r->shadow_t < pos.t_max && r->shadow_t > 0.0001)
	{
		if (r->obj[i].transperency == 0)
			return (0);
		else if (r->shad_trans > r->obj[i].transperency && r->shadow_t > 0.1)
			r->shad_trans = r->obj[i].transperency;
	}
	return (r->shad_trans);
}

double	ft_shadow_cone(t_rt *r, t_raydata *ray, t_vecs pos, int i)
{
	r->shadow_t = ft_intersect_ray_cone(&r->obj[i], ray);
	if (r->shadow_t < pos.t_max && r->shadow_t > 0.0001)
	{
		if (r->obj[i].transperency == 0)
			return (0);
		else if (r->shad_trans > r->obj[i].transperency && r->shadow_t > 0.1)
			r->shad_trans = r->obj[i].transperency;
	}
	return (r->shad_trans);
}

double	ft_shadow_paraboloid(t_rt *r, t_raydata *ray, t_vecs pos, int i)
{
	r->shadow_t = ft_paraboloid_inter(ray, &r->obj[i]);
	if (r->shadow_t < pos.t_max && r->shadow_t > 0.0001)
	{
		if (r->obj[i].transperency == 0)
			return (0);
		else if (r->shad_trans > r->obj[i].transperency && r->shadow_t > 0.1)
			r->shad_trans = r->obj[i].transperency;
	}
	return (r->shad_trans);
}

double	ft_shadow_cube(t_rt *r, t_raydata *ray, t_vecs pos, int i)
{
	r->shadow_t = ft_cube_ray(ray, &r->obj[i], 0);
	if (r->shadow_t < pos.t_max && r->shadow_t > 0.0001)
	{
		if (r->obj[i].transperency == 0)
			return (0);
		else if (r->shad_trans > r->obj[i].transperency && r->shadow_t > 0.1)
			r->shad_trans = r->obj[i].transperency;
	}
	return (r->shad_trans);
}

double	ft_shadow1(t_rt *r, t_raydata *ray, t_vecs pos, int i)
{
	if (ft_strequ(r->obj[i].name, "torus") &&\
		(!(ft_shadow_torus(r, ray, pos, i))))
		return (0);
	else if (ft_strequ(r->obj[i].name, "cone") &&\
		(!(ft_shadow_cone(r, ray, pos, i))))
		return (0);
	else if (ft_strequ(r->obj[i].name, "paraboloid") && \
		(!(ft_shadow_paraboloid(r, ray, pos, i))))
		return (0);
	else if (ft_strequ(r->obj[i].name, "cube") && \
		(!(ft_shadow_cube(r, ray, pos, i))))
		return (0);
	return (r->shad_trans);
}
