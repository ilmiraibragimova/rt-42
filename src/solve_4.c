/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 22:28:41 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 22:29:11 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		ft_equition8(double *x, double b, double d)
{
	double t;
	double s[6];

	t = b * b - 4 * d;
	if (t >= 0)
	{
		s[0] = sqrt(t);
		s[1] = (-b + s[0]) / 2;
		s[2] = (-b - s[0]) / 2;
		if (s[1] < 0)
			return (0);
		s[3] = sqrt(-s[2]);
		s[4] = sqrt(s[1]);
		s[5] = sqrt(s[2]);
		x[0] = -s[4];
		x[1] = s[4];
		x[2] = s[2] >= 0 ? -s[5] : 0;
		x[3] = s[2] >= 0 ? s[5] : s[3];
		return (s[2] >= 0 ? 4 : 2);
	}
	else
		return (0);
}

static double	ft_equition7(double x, t_equl equl)
{
	double	fxs;
	double	fx;

	fxs = ((4 * x * 3 * equl.a) * x + 2 * equl.b) * x + equl.c;
	if (fxs == 0)
		return (x);
	fx = (((x + equl.a) * x + equl.b) * x + equl.c) * x + equl.d;
	return (x - fx / fxs);
}

static int		ft_equition6(double *x, double c)
{
	double	sz1;
	double	szr;
	double	szi;
	double	r;

	sz1 = sqrt(x[0]);
	r = sqrt(x[1] * x[1] + x[2] * x[2]);
	if (x[2] == 0)
	{
		r = sqrt(r);
		szr = x[1] >= 0 ? r : 0;
		szi = x[1] >= 0 ? 0 : r;
	}
	else
	{
		szr = sqrt(0.5 * (x[1] + r));
		szi = 0.5 * x[2] / szr;
	}
	x[0] = c > 0 ? -sz1 / 2 - szr : sz1 / 2 - szr;
	x[1] = c > 0 ? -sz1 / 2 + szr : sz1 / 2 + szr;
	x[2] = c > 0 ? sz1 / 2 : -sz1 / 2;
	x[3] = szi;
	return (2);
}

static int		ft_solve_4(double *x, double b,\
	double c, double d)
{
	int		res;
	double	s[3];

	if (fabs(c) < 1e-14 * (fabs(b) + fabs(d)))
		return (ft_equition8(x, b, d));
	res = ft_equation_3(x, 2 * b, b * b - 4 * d, -c * c);
	if (res > 1)
	{
		ft_sort(x);
		if (x[0] > 0)
		{
			s[0] = sqrt(x[0]);
			s[1] = sqrt(x[1]);
			s[2] = sqrt(x[2]);
			x[0] = c > 0 ? (-s[0] - s[1] - s[2]) / 2 : (s[2] - s[1] - s[0]) / 2;
			x[1] = c > 0 ? (-s[0] + s[1] + s[2]) / 2 : (s[1] - s[0] - s[2]) / 2;
			x[2] = c > 0 ? (s[0] - s[1] + s[2]) / 2 : (s[0] - s[1] - s[2]) / 2;
			x[3] = c > 0 ? (s[0] + s[1] - s[2]) / 2 : (s[0] + s[1] + s[2]) / 2;
			return (4);
		}
		return (0);
	}
	x[0] = x[0] < 0 ? 0 : x[0];
	return (ft_equition6(x, c));
}

int				ft_equation_4(t_equl equl, double *x)
{
	int	res;

	equl.m = equl.d + 0.25 * equl.a * (0.25 * equl.b * equl.a\
		- 3. / 64 * equl.a * equl.a * equl.a - equl.c);
	equl.n = equl.c + 0.5 * equl.a * (0.25 * equl.a * equl.a - equl.b);
	equl.o = equl.b - 0.375 * equl.a * equl.a;
	res = ft_solve_4(x, equl.o, equl.n, equl.m);
	x[3] = res == 4 ? x[3] - equl.a / 4 : x[3];
	x[1] = res == 2 || res == 4 ? x[1] - equl.a / 4 : x[1];
	x[0] -= equl.a / 4;
	x[2] -= equl.a / 4;
	if (res > 0)
	{
		x[0] = ft_equition7(x[0], equl);
		x[1] = ft_equition7(x[1], equl);
	}
	if (res > 2)
	{
		x[2] = ft_equition7(x[2], equl);
		x[3] = ft_equition7(x[3], equl);
	}
	return (res);
}
