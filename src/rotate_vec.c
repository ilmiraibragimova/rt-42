/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 20:46:16 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 20:46:16 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rotate_x(double angle, t_vec *vec)
{
	double	rad;
	double	cos_v;
	double	sin_v;
	t_vec	old;

	old = *vec;
	rad = M_PI / 180 * angle;
	cos_v = cos(rad);
	sin_v = sin(rad);
	vec->x = old.x;
	vec->y = old.y * cos_v - old.z * sin_v;
	vec->z = old.y * sin_v + old.z * cos_v;
}

void		rotate_y(double angle, t_vec *vec)
{
	double	rad;
	double	cos_v;
	double	sin_v;
	t_vec	old;

	old = *vec;
	rad = M_PI / 180 * angle;
	cos_v = cos(rad);
	sin_v = sin(rad);
	vec->x = old.x * cos_v + old.z * sin_v;
	vec->y = old.y;
	vec->z = -old.x * sin_v + old.z * cos_v;
}

static void	rotate_z(double angle, t_vec *vec)
{
	double	rad;
	double	cos_v;
	double	sin_v;
	t_vec	old;

	old = *vec;
	rad = M_PI / 180 * angle;
	cos_v = cos(rad);
	sin_v = sin(rad);
	vec->x = old.x * cos_v - old.y * sin_v;
	vec->y = old.x * sin_v + old.y * cos_v;
	vec->z = old.z;
}

t_vec		rotate_vec(t_vec angle, t_vec a)
{
	rotate_x(angle.x, &a);
	rotate_y(angle.y, &a);
	rotate_z(angle.z, &a);
	return (a);
}
