/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transperency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 23:21:06 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 23:24:34 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	ray_trans(t_vec ray_dir, t_vec normal, double mat_ref)
{
	double eta;
	double cos_theta;
	double k;

	eta = 1.0 / mat_ref;
	cos_theta = -vec_dot(normal, ray_dir);
	if (cos_theta < 0)
	{
		cos_theta *= -1.0;
		normal = vec_scale(normal, -1.0);
		eta = 1.0 / eta;
	}
	k = 1.0 - eta * eta * (1.0 - cos_theta * cos_theta);
	if (k >= 0.0)
		ray_dir = vec_sum(vec_norm(vec_scale(ray_dir, eta)), \
			vec_scale(normal, (eta * cos_theta - sqrt(k))));
	return (ray_dir);
}

t_vec	reflect_ray(t_vec r, t_vec n)
{
	return (vec_sub(vec_scale(n, 2 * vec_dot(n, r)), r));
}
