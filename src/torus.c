/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 23:18:01 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/31 21:40:31 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_equation(t_equl eq, int f)
{
	double	d[4];
	int		res;
	int		i;
	double	t;

	i = -1;
	t = INFINITY;
	res = ft_equation_4(eq, d);
	if (res == 0)
		return (INFINITY);
	if (f == 0)
		while (++i < res)
		{
			if (d[i] < t && d[i] > 0.001)
				t = d[i];
		}
	if (f == 1)
		while (++i < res)
		{
			if (d[i] < t)
				t = d[i];
		}
	return (t);
}

double	ft_ray_torus(t_raydata *ray, t_obj *t, int f)
{
	t_equl	equl;
	t_vec	oc;

	oc = vec_sub(t->center, ray->point);
	equl.m = 1 - pow(vec_dot(t->rot, ray->direction), 2);
	equl.n = 2 * (vec_dot(oc, ray->direction) -\
		vec_dot(t->rot, oc) * vec_dot(t->rot, ray->direction));
	equl.o = vec_dot(oc, oc) -\
		pow(vec_dot(t->rot, oc), 2);
	equl.p = vec_dot(oc, oc) + t->max * t->max - t->min * t->min;
	equl.a = 4 * vec_dot(oc, ray->direction);
	equl.b = 2 * equl.p + equl.a * equl.a * 0.25 - 4 * equl.m * t->max * t->max;
	equl.c = equl.a * equl.p - 4 * equl.n * t->max * t->max;
	equl.d = equl.p * equl.p - 4 * t->max * t->max * equl.o;
	return (ft_equation(equl, f));
}

t_vec	ft_norm_torus(t_obj *obj)
{
	t_vec	tmp;
	t_vec	normal;
	double	dot;
	double	m;

	dot = vec_dot(vec_sub(obj->center, obj->p), obj->rot);
	tmp = vec_sub(vec_scale(obj->rot, dot), obj->p);
	m = sqrt(obj->min * obj->min - dot * dot);
	normal = vec_norm(vec_sub(obj->p, vec_sub(tmp, \
	vec_scale(vec_sub(tmp, obj->center), m / (obj->max + m)))));
	return (normal);
}
