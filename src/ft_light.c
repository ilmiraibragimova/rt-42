/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:18:17 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/01 20:45:15 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_lighting2(t_rt *r, t_light light, t_vec l, t_raydata ray)
{
	t_vec	r1;
	double	r_dot_v;
	double	nl;

	nl = vec_dot(r->obj[r->clos].n, l);
	if (((nl > 0) && (vec_dot(r->obj[r->clos].n, ray.direction) < 0)) \
		|| (nl < 0 && (vec_dot(r->obj[r->clos].n, ray.direction) > 0) \
		&& ((bord(r, &light)) || ft_strequ(r->obj[r->clos].name, "plane"))))
	{
		if (nl < 0)
			nl = -nl;
		r->intensity += (light.intensity * nl / \
			(vec_len(r->obj[r->clos].n) * vec_len(l))) * r->obj[r->clos].shad;
	}
	if (r->obj[r->clos].specular != -1)
	{
		r1 = vec_sub(l, vec_scale(r->obj[r->clos].n, \
		(2 * vec_dot(r->obj[r->clos].n, l))));
		r_dot_v = vec_dot(r1, vec_scale(ray.direction, -1));
		if (r_dot_v > 0 && nl > 0)
			r->intensity += light.intensity * pow(r_dot_v / (vec_len(r1) \
			* vec_len(vec_scale(ray.direction, -1))), r->obj[r->clos].specular);
	}
}

t_vecs		ft_lighting3(t_light light, t_vecs vecs, t_vec p)
{
	if (ft_strequ(light.type, "point"))
	{
		vecs.l = vec_sub(p, light.position);
		vecs.t_max = vec_len(vecs.l);
		vecs.k = light.position;
	}
	else
	{
		vecs.l = vec_norm(light.direction);
		vecs.t_max = INFINITY;
		vecs.k = light.direction;
	}
	return (vecs);
}

double		lighting(t_rt *r, t_vec p, t_raydata vew)
{
	t_vecs	vecs;
	int		i;

	r->intensity = 0.0;
	i = -1;
	while (++i < r->amount_ligth)
	{
		if (ft_strequ(r->light[i].type, "ambient"))
			r->intensity += r->light[i].intensity;
		else
		{
			vecs = ft_lighting3(r->light[i], vecs, p);
			r->obj[r->clos].shad = ft_shadow(r, p, vecs);
			if ((r->obj[r->clos].shad != 0))
				ft_lighting2(r, r->light[i], vecs.l, vew);
		}
	}
	if (r->intensity > 1)
		r->intensity = 1;
	return (r->intensity);
}
