/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:19:01 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/30 20:04:10 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_get_t(double k1, double k2, double k3, int f)
{
	double	t[2];
	double	discriminant;

	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
		return (INFINITY);
	else
	{
		t[0] = (-k2 + sqrt(discriminant)) / (2 * k1);
		t[1] = (-k2 - sqrt(discriminant)) / (2 * k1);
		if (f == 1 && t[0] < t[1])
			return (t[0]);
		if (f == 1 && t[1] < t[0])
			return (t[1]);
		if ((t[0] < t[1] && t[0] > 0.001) || (t[1] < 0 && t[0] > 0.001))
			return (t[0]);
		else if ((t[1] < t[0] && t[1] > 0.001) || (t[0] < 0 && t[1] > 0.001))
			return (t[1]);
		else
			return (INFINITY);
	}
}

double	ray_sphere(t_raydata vew, t_obj obj, int f)
{
	double	r1;
	double	k1;
	double	k2;
	double	k3;
	t_vec	oc;

	oc = vec_sub(obj.center, vew.point);
	r1 = obj.radius;
	k1 = vec_dot(vew.direction, vew.direction);
	k2 = 2.0 * vec_dot(oc, vew.direction);
	k3 = vec_dot(oc, oc) - r1 * r1;
	return (ft_get_t(k1, k2, k3, f));
}
