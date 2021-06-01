/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:45:28 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/26 18:46:21 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	ft_norm_sphere(t_vec p, t_rt *r)
{
	t_vec n;

	n = vec_sub(r->obj[r->clos].center, p);
	n = vec_norm(n);
	return (n);
}

t_vec	ft_norm_plane(t_rt *r)
{
	return (r->obj[r->clos].rot);
}

t_vec	ft_norm_con(t_vec vew, t_vec p, t_rt *r)
{
	t_vec	normal;
	double	k;
	double	m;

	k = tan(0.5 * (r->obj->radius * M_PI / 180.0));
	m = r->closest_t * vec_dot(vew, r->obj[r->clos].rot) +\
		vec_dot(vec_sub(r->obj[r->clos].center, r->cam.point),\
		r->obj[r->clos].rot);
	k = (k * k + 1.0) * m;
	normal = vec_sub(r->obj[r->clos].center, p);
	normal = vec_sub(vec_scale(r->obj[r->clos].rot, k), normal);
	normal = vec_norm(normal);
	return (normal);
}

t_vec	ft_norm_cylinder(t_vec vew, t_vec p, t_rt *r)
{
	double	m;
	t_vec	n;

	r->obj->rot = vec_norm(r->obj->rot);
	m = r->closest_t * vec_dot(vew, r->obj[r->clos].rot) +\
		vec_dot(vec_sub(r->cam.point, r->obj[r->clos].center),\
		r->obj[r->clos].rot);
	n = vec_norm(vec_sub(vec_scale(r->obj[r->clos].rot, m), \
	vec_sub(r->obj[r->clos].center, p)));
	return (vec_scale(n, 1));
}

void	matr_normal(t_matr *m)
{
	double	matr_len;

	matr_len = sqrt(m->l * m->l + m->vec.x * m->vec.x + \
		m->vec.y * m->vec.y + m->vec.z * m->vec.z);
	m->l /= matr_len;
	m->vec.x /= matr_len;
	m->vec.y /= matr_len;
	m->vec.z /= matr_len;
}
