/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 20:58:47 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 21:16:26 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

static double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = h < 8 || h == 12 || h == 13 ? x : y;
	v = h < 4 || h == 12 || h == 13 ? y : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double			calc_noise(t_vec tmp, t_vec coords, int vals[6], int perlin[])
{
	return (lerp(tmp.z, lerp(tmp.y, lerp(tmp.x,\
		grad(perlin[vals[1]], coords.x, coords.y, coords.z),\
		grad(perlin[vals[4]], coords.x - 1, coords.y, coords.z)),\
		lerp(tmp.x,\
		grad(perlin[vals[2]], coords.x, coords.y - 1, coords.z),\
		grad(perlin[vals[5]], coords.x - 1, coords.y - 1, coords.z))),\
		lerp(tmp.y, lerp(tmp.x,\
		grad(perlin[vals[1] + 1], coords.x, coords.y, coords.z - 1),\
		grad(perlin[vals[4] + 1], coords.x - 1, coords.y, coords.z - 1)),\
		lerp(tmp.x, grad(perlin[vals[2] + 1],\
		coords.x, coords.y - 1, coords.z - 1),\
		grad(perlin[vals[5] + 1], coords.x - 1, coords.y - 1, coords.z - 1)))));
}

t_vec			find_pos(double x, double y, double z)
{
	t_vec pos;

	pos.x = (int)floor(x) & 255;
	pos.y = (int)floor(y) & 255;
	pos.z = (int)floor(z) & 255;
	return (pos);
}

double			noise(double x, double y, double z)
{
	t_vec	pos;
	t_vec	tmp;
	t_vec	coords;
	int		vals[6];
	int		perlin[512];

	init_perlin(perlin);
	pos = find_pos(x, y, z);
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	coords.x = x;
	coords.y = y;
	coords.z = z;
	tmp.x = (x * x * x * (x * (x * 6 - 15) + 10));
	tmp.y = (y * y * y * (y * (y * 6 - 15) + 10));
	tmp.z = (z * z * z * (z * (z * 6 - 15) + 10));
	vals[0] = perlin[(int)pos.x] + (int)pos.y;
	vals[1] = perlin[vals[0]] + (int)pos.z;
	vals[2] = perlin[vals[0] + 1] + (int)pos.z;
	vals[3] = perlin[(int)pos.x + 1] + (int)pos.y;
	vals[4] = perlin[vals[3]] + (int)pos.z;
	vals[5] = perlin[vals[3] + 1] + (int)pos.z;
	return (calc_noise(tmp, coords, vals, perlin));
}
