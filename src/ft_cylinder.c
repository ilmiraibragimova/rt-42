/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:51:37 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/01 20:15:37 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	calculate_abc_discr_cylinder(t_obj *cylinder, t_raydata *ray, \
	t_equl *equl)
{
	t_vec	x;

	x = vec_sub(cylinder->center, ray->point);
	equl->a = vec_dot(ray->direction, ray->direction) - \
		pow(vec_dot(ray->direction, cylinder->rot), 2);
	equl->b = 2 * (vec_dot(ray->direction, x) - \
		(vec_dot(ray->direction, cylinder->rot) * vec_dot(x, cylinder->rot)));
	equl->c = vec_dot(x, x) - pow(vec_dot(x, cylinder->rot), 2)\
		- pow(cylinder->radius, 2);
}

double		intersect_ray_cylinder(t_obj *tube, t_raydata *ray)
{
	double	check;
	t_equl	equl;

	ray->st_cent = vec_sub(ray->point, tube->center);
	calculate_abc_discr_cylinder(tube, ray, &equl);
	solve_quadratic_equation(&equl);
	if (equl.d < 0.001)
		return (INFINITY);
	check = check_intersect(&ray->direction, \
		&ray->st_cent, &tube->rot, equl.d1);
	if (tube->max >= check && check >= tube->min)
	{
		return (equl.d1);
	}
	check = check_intersect(&ray->direction, &ray->st_cent, \
		&tube->rot, equl.d2);
	if (tube->max >= check && check >= tube->min)
	{
		return (equl.d2);
	}
	return (INFINITY);
}
