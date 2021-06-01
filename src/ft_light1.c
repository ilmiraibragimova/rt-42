/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:30:29 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/10 16:23:31 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_found_n(t_rt *r, t_raydata vew)
{
	if (ft_strequ(r->obj[r->clos].name, "sphere"))
		r->obj[r->clos].n = ft_norm_sphere(r->obj[r->clos].p, r);
	else if (ft_strequ(r->obj[r->clos].name, "plane"))
		r->obj[r->clos].n = ft_norm_plane(r);
	else if (ft_strequ(r->obj[r->clos].name, "cone"))
		r->obj[r->clos].n = ft_norm_con(vew.direction, r->obj[r->clos].p, r);
	else if (ft_strequ(r->obj[r->clos].name, "cylinder"))
		r->obj[r->clos].n = ft_norm_cylinder(vew.direction,\
			r->obj[r->clos].p, r);
	else if (ft_strequ(r->obj[r->clos].name, "torus"))
		r->obj[r->clos].n = ft_norm_torus(&r->obj[r->clos]);
	else if (ft_strequ(r->obj[r->clos].name, "cube"))
		r->obj[r->clos].n = norm_cube(r);
	else
		r->obj[r->clos].n = ft_paraboloid_norm(&r->obj[r->clos]);
}

void	ft_found_tex(t_rt *r)
{
	double n;

	if (r->obj[r->clos].flag_tex == 1)
		r->obj[r->clos].color1 = pattern_at(r->obj[r->clos].p, \
			r, r->obj[r->clos].color);
	else if (r->obj[r->clos].flag_tex == 2)
	{
		n = noise((r->d1.x + r->per_data.x_per) * r->obj[r->clos].t_h, \
		(r->d1.y + r->per_data.y_per) * r->obj[r->clos].t_w,\
		(r->d1.z + r->per_data.z_per) * 100);
		r->obj[r->clos].color1 = vec_scale((t_vec) {r->obj[r->clos].color.x, \
		r->obj[r->clos].color.y, r->obj[r->clos].color.z}, n);
		if (r->obj[r->clos].color1.y < 0)
			r->obj[r->clos].color1.y = 255;
		if (r->obj[r->clos].color1.x < 0)
			r->obj[r->clos].color1.x = 255;
		if (r->obj[r->clos].color1.z < 0)
			r->obj[r->clos].color1.z = 255;
	}
	else if (r->obj[r->clos].flag_tex == 3)
		r->obj[r->clos].color1 = calculate_texture_color(r);
	else if (r->obj[r->clos].flag_tex != 0)
		ft_put_error("Wrong texture number");
}

void	ft_transparency(t_rt *r, t_raydata vew)
{
	double		r2;
	t_vec		trans;
	t_raydata	ray2;
	t_vec		s;
	t_vec		trans_color;

	r2 = r->obj[r->clos].transperency;
	trans = ray_trans(vew.direction, r->obj[r->clos].n, 1.05);
	ray2.point = r->obj[r->clos].p;
	ray2.direction = trans;
	s = r->obj[r->clos].color1;
	trans_color = ft_traceray(&ray2, r, 1, 2);
	r->obj[r->clos].color1 = \
	vec_sum(vec_scale(s, (1 - r2)), vec_scale(trans_color, r2));
}

void	ft_reflect(t_rt *r, t_raydata vew, int depth)
{
	double		r1;
	t_vec		ref;
	t_raydata	ray1;
	t_vec		s;
	t_vec		reflected_color;

	r1 = r->obj[r->clos].reflect;
	ref = reflect_ray(vew.direction, r->obj[r->clos].n);
	ray1.point = r->obj[r->clos].p;
	ray1.direction = ref;
	s = r->obj[r->clos].color1;
	reflected_color = ft_traceray(&ray1, r, 1, depth - 1);
	r->obj[r->clos].color1 = vec_sum(vec_scale(s, (1 - r1)), \
		vec_scale(reflected_color, r1));
}

t_vec	ft_lighting1(t_rt *r, t_raydata vew, int depth)
{
	r->obj[r->clos].p = vec_sum(vew.point, vec_scale(vew.direction,\
		r->closest_t));
	ft_found_n(r, vew);
	r->obj[r->clos].color1 = r->obj[r->clos].color;
	ft_found_tex(r);
	r->obj[r->clos].color1 = vec_scale(r->obj[r->clos].color1, \
		lighting(r, r->obj[r->clos].p, vew));
	if (r->obj[r->clos].transperency > 0)
		ft_transparency(r, vew);
	if (depth > 0 && r->obj[r->clos].reflect > 0)
		ft_reflect(r, vew, depth);
	if (r->obj[r->clos].color1.y > 255)
		r->obj[r->clos].color1.y = 255;
	if (r->obj[r->clos].color1.x > 255)
		r->obj[r->clos].color1.x = 255;
	if (r->obj[r->clos].color1.z > 255)
		r->obj[r->clos].color1.z = 255;
	return (r->obj[r->clos].color1);
}
