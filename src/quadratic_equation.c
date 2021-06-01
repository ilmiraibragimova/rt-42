/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_equation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 21:22:04 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 21:22:04 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_swap_double(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	solve_quadratic_equation(t_equl *discr)
{
	discr->d1 = -1;
	discr->d2 = -1;
	discr->d = (double)(discr->b * discr->b - 4 * discr->a * discr->c);
	if (discr->d >= 0)
	{
		discr->o = sqrtf(discr->d);
		discr->a = 2 * discr->a;
		discr->d1 = (-discr->b + discr->o) / discr->a;
		discr->d2 = (-discr->b - discr->o) / discr->a;
		if (discr->d1 >= 0.001f && discr->d2 >= 0.001f)
		{
			if (discr->d1 > discr->d2)
				ft_swap_double(&discr->d1, &discr->d2);
		}
		if (discr->d1 < 0.001f && discr->d2 > 0.001f)
			ft_swap_double(&discr->d1, &discr->d2);
	}
}
