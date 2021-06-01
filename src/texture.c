/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 22:30:31 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 22:46:45 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	uv_pattern_at(t_textr *checkers, double u, double v, t_vec s)
{
	double	u2;
	double	v2;

	u2 = floor(u * (checkers->w - 1));
	v2 = floor(v * (checkers->h - 1));
	if ((int)(u2 + v2) % 2 == 0)
		s = vec_scale(checkers->color_a, 1);
	else
		s = vec_scale(checkers->color_b, 1);
	return (s);
}

void	pattern_at_f(t_textr *texture_map, t_rt *r)
{
	texture_map->h = r->obj[r->clos].t_h;
	texture_map->w = r->obj[r->clos].t_w;
}

t_vec	pattern_at(t_vec p, t_rt *r, t_vec s)
{
	t_textr	*texture_map;
	double	u_v[2];

	if (!(texture_map = (t_textr*)malloc(sizeof(t_textr))))
		ft_put_error("Allocation memory error");
	pattern_at_f(texture_map, r);
	if (r->obj[r->clos].t_col == 0)
	{
		texture_map->color_a.x = 255;
		texture_map->color_a.y = 255;
		texture_map->color_a.z = 255;
	}
	else
	{
		texture_map->color_a.x = 0;
		texture_map->color_a.y = 0;
		texture_map->color_a.z = 0;
	}
	texture_map->color_b.x = s.x;
	texture_map->color_b.y = s.y;
	texture_map->color_b.z = s.z;
	spherical_map(p, r, u_v);
	s = uv_pattern_at(texture_map, u_v[0], u_v[1], s);
	free(texture_map);
	return (s);
}
