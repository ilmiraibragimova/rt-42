/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:00:18 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/30 13:00:18 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "veclib.h"

t_vec	vec_cross(t_vec va, t_vec vb)
{
	t_vec	v;

	v.x = va.y * vb.z - va.z * vb.y;
	v.y = va.z * vb.x - va.x * vb.z;
	v.z = va.x * vb.y - va.y * vb.x;
	return (v);
}

t_vec	vec_mul(t_vec va, t_vec vb)
{
	t_vec	v;

	v.x = va.x * vb.x;
	v.y = va.y * vb.y;
	v.z = va.z * vb.z;
	return (v);
}
