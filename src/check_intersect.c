/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:15:44 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/26 17:17:51 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_vector_scalar(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

double	ft_vector_modul(t_vec *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

double	ft_vector_projection_on_ray(t_vec *v1, t_vec *v2)
{
	return (ft_vector_scalar(v1, v2) / ft_vector_modul(v2));
}

double	check_intersect(t_vec *ray, t_vec *pos, t_vec *axis, double len)
{
	t_vec	intersect;
	double	check;

	intersect = vec_scale(*ray, len);
	intersect = vec_sub(intersect, *pos);
	check = ft_vector_projection_on_ray(&intersect, axis);
	return (check);
}
