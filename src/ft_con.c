/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_con.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:29:38 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/02 13:16:40 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	calculate_a_b_c_discr_cone(t_raydata *ray, t_obj *cone,\
	t_equl *equl)
{
	double	dot_ov_r;
	double	k;

	dot_ov_r = vec_dot(ray->direction, cone->rot);
	k = tan(0.5 * (cone->radius * M_PI / 180));
	k = k * k + 1.0;
	equl->a = vec_dot(ray->direction, ray->direction) - k * pow(dot_ov_r, 2.0);
	equl->b = 2.0 * (vec_dot(ray->direction, ray->st_cent)\
		- k * vec_dot(ray->st_cent, cone->rot) * dot_ov_r);
	equl->c = vec_dot(ray->st_cent, ray->st_cent) - \
		k * pow(vec_dot(ray->st_cent, cone->rot), 2.0);
}

double		ft_intersect_ray_cone(t_obj *cone, t_raydata *ray)
{
	t_equl	equl;

	ray->st_cent = vec_sub(cone->center, ray->point);
	calculate_a_b_c_discr_cone(ray, cone, &equl);
	solve_quadratic_equation(&equl);
	if (equl.d < 0.0001)
		return (INFINITY);
	if (cone->is_limit && !ft_is_limit(ray, equl, cone))
		return (INFINITY);
	return (ft_dist(equl, ray, cone));
}
