/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:19:21 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/26 17:26:19 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	norm_cube(t_rt *r)
{
	t_vec	normal;
	t_vec	p;

	p = r->obj[r->clos].p;
	normal = (t_vec){4 * pow(p.x, 3) - 10 * p.x, 4 *\
		pow(p.y, 3) - 10 * p.y, 4 * pow(p.z, 3) - 10 * p.z};
	normal = vec_norm(normal);
	return (normal);
}

double	ft_cube_ray(t_raydata *ray, t_obj *c, int f)
{
	t_equl	equl;

	equl.tmp = pow(ray->direction.x, 4) + \
		pow(ray->direction.y, 4) + pow(ray->direction.z, 4);
	equl.a = 4.0 * (pow(ray->direction.x, 3) * ray->point.x +\
		pow(ray->direction.y, 3) * ray->point.y + pow(ray->direction.z, 3)\
		* ray->point.z);
	equl.b = 6.0 * (pow(ray->direction.x, 2) * pow(ray->point.x, 2)\
		+ pow(ray->direction.y, 2) * pow(ray->point.y, 2)\
		+ pow(ray->direction.z, 2) * pow(ray->point.z, 2)) - 5.0\
		* vec_dot(ray->direction, ray->direction);
	equl.c = 4.0 * (pow(ray->point.x, 3) * ray->direction.x\
		+ pow(ray->point.y, 3)\
		* ray->direction.y + pow(ray->point.z, 3) * ray->direction.z) - 10.0\
		* vec_dot(ray->direction, ray->point);
	equl.d = pow(ray->point.x, 4) + pow(ray->point.y, 4) + pow(ray->point.z, 4)\
		- 5.0 * vec_dot(ray->point, ray->point) + c->radius;
	equl.a = equl.a / equl.tmp;
	equl.b = equl.b / equl.tmp;
	equl.c = equl.c / equl.tmp;
	equl.d = equl.d / equl.tmp;
	return (ft_equation(equl, f));
}
