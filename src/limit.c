/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:43:20 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/01 20:44:36 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_limit1(double t, t_raydata *ray, t_vec *limits)
{
	t_vec p;

	p = vec_sum(vec_scale(ray->direction, t), ray->point);
	if ((((p.x > 0 && limits->x > 0 && p.x > limits->x)\
		|| (p.x < 0 && limits->x < 0 && p.x < limits->x))\
		|| ((p.y > 0 && limits->y > 0 && p.y > limits->y)\
		|| (p.y < 0 && limits->y < 0 && p.y < limits->y))\
		|| ((p.z > 0 && limits->z > 0 && p.z > limits->z)\
		|| (p.z < 0 && limits->z < 0 && p.z < limits->z))))
		return (1);
	return (0);
}

double	ft_dist(t_equl t, t_raydata *ray, t_obj *obj)
{
	if ((t.d2 <= t.d1 || t.d1 < 0.001) && t.d2 > 0.001)
	{
		if (obj->is_limit && ft_limit1(t.d2, ray, &obj->limit))
			return (INFINITY);
		return (t.d2);
	}
	else if ((t.d1 < t.d2 || t.d2 < 0.001) && t.d1 > 0.001)
	{
		if (obj->is_limit && ft_limit1(t.d1, ray, &obj->limit))
			return (INFINITY);
		return (t.d1);
	}
	return (INFINITY);
}

int		ft_is_limit(t_raydata *ray, t_equl t, t_obj *cyl)
{
	t_vec	x;
	double	m;
	double	m1;

	x = vec_sub(ray->point, cyl->center);
	m = vec_dot(ray->direction, vec_scale(cyl->rot, t.d1)) + \
	vec_dot(x, cyl->rot);
	m1 = vec_dot(ray->direction, vec_scale(cyl->rot, t.d2)) + \
	vec_dot(x, cyl->rot);
	if (cyl->limit1 && ((m > cyl->limit1 && m1 > cyl->limit1)\
	|| (m < -1 * cyl->limit1 && m1 < -1 * cyl->limit1)))
		return (0);
	return (1);
}
