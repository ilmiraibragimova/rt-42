/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 11:15:34 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/11 16:43:35 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_paraboloid_inter(t_raydata *ray, t_obj *obj)
{
	t_vec	dist;
	double	dsq;
	double	abc[3];
	double	t[2];

	abc[0] = vec_dot(ray->direction, ray->direction) -\
		pow(vec_dot(ray->direction, obj->rot), 2);
	dist = vec_sub(obj->center, ray->point);
	abc[1] = 2 * (vec_dot(ray->direction, dist) - vec_dot(ray->direction,\
		obj->rot) * (vec_dot(dist, obj->rot) + 2 * obj->scale2));
	abc[2] = vec_dot(dist, dist) - vec_dot(dist, obj->rot)\
		* (vec_dot(dist, obj->rot) + 4 * obj->scale2);
	dsq = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (dsq < 0)
		return (INFINITY);
	dsq = sqrt(dsq);
	t[0] = (-abc[1] + dsq) / (2 * abc[0]);
	t[1] = (-abc[1] - dsq) / (2 * abc[0]);
	if ((t[0] < t[1] && t[0] > 0.0001) || (t[1] < 0 && t[0] > 0.00001))
		return (t[0]);
	else if ((t[1] < t[0] && t[1] > 0.0001) || (t[0] < 0 && t[1] > 0.00001))
		return (t[1]);
	else
		return (INFINITY);
}

t_vec	ft_paraboloid_norm(t_obj *parab)
{
	double	m;
	t_vec	normal;

	m = vec_dot(vec_sub(parab->p, parab->center), parab->rot);
	normal = vec_sub(vec_sub(parab->p, parab->center),\
		vec_scale(parab->rot, (m + parab->scale2)));
	return (vec_norm(normal));
}
