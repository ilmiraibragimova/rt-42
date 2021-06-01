/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 22:56:58 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/10 18:22:25 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	texture_sphere(t_rt *r, t_vec p, double u_v[2])
{
	double theta;
	double phi;
	double raw_u;

	p = vec_norm(vec_sub(p, r->obj[r->clos].center));
	theta = atan2(p.z, p.x);
	phi = acos(p.y / r->obj[r->clos].radius);
	raw_u = theta / (2 * M_PI);
	u_v[0] = (raw_u + 0.5);
	u_v[1] = 1 - phi / M_PI;
}

void	texture_plane(t_rt *r, t_vec p, double u_v[2])
{
	t_vec u_axis;
	t_vec v_axis;

	u_axis = (t_vec) {r->obj[r->clos].n.y, \
		r->obj[r->clos].n.z, -r->obj[r->clos].n.x};
	v_axis = vec_cross(u_axis, r->obj[r->clos].n);
	u_v[0] = vec_dot(p, u_axis);
	u_v[1] = vec_dot(p, v_axis);
	if (r->obj[r->clos].flag_tex == 3)
	{
		if (u_v[0] < 0)
			u_v[0] = -u_v[0];
		if (u_v[1] < 0)
			u_v[1] = -u_v[1];
		u_v[0] = u_v[0] - (int)u_v[0];
		u_v[1] = u_v[1] - (int)u_v[1];
	}
}

void	texture_cyl(t_rt *r, t_vec p, double u_v[2])
{
	t_vec	cross;

	p = vec_sub(p, vec_mul(r->obj[r->clos].center, r->obj[r->clos].rot));
	cross = vec_cross(r->obj[r->clos].rot, p);
	u_v[0] = vec_dot(cross, (t_vec){0, 0, 0.5}) / (r->obj[r->clos].t_w);
	if ((r->obj[r->clos].limit1) > 0)
		u_v[1] = vec_dot(p, r->obj[r->clos].rot) / \
		(r->obj[r->clos].limit1);
	else
		u_v[1] = vec_dot(p, r->obj[r->clos].rot) / (r->obj[r->clos].t_h);
	if (u_v[0] < 0)
		u_v[0] = -u_v[0];
	if (u_v[1] < 0)
		u_v[1] = -u_v[1];
}

double	*spherical_map(t_vec p, t_rt *r, double u_v[])
{
	if (ft_strequ(r->obj[r->clos].name, "plane"))
		texture_plane(r, p, u_v);
	else if (ft_strequ(r->obj[r->clos].name, "sphere"))
		texture_sphere(r, p, u_v);
	else if (ft_strequ(r->obj[r->clos].name, "cone") ||\
		(ft_strequ(r->obj[r->clos].name, "cylinder")))
		texture_cyl(r, p, u_v);
	return (u_v);
}
