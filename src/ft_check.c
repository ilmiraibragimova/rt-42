/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:17:45 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/30 12:17:51 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_cone(t_obj *cone)
{
	if (cone->radius < 0.1 ||
		cone->color.x < 0 || cone->color.x > 255 ||
		cone->color.y < 0 || cone->color.y > 255 ||
		cone->color.z < 0 || cone->color.z > 255 ||
		cone->transperency > 1 || cone->reflect > 1)
		error_cone();
}

void	check_cylinder(t_obj *cyl)
{
	if (cyl->color.x < 0 || cyl->color.x > 255
		|| cyl->color.y < 0 || cyl->color.y > 255
		|| cyl->color.z < 0 || cyl->color.z > 255
		|| cyl->transperency > 1 || cyl->reflect > 1 ||
		cyl->radius < 0.1)
		error_cyl();
}

void	check_parab(t_obj *plane)
{
	if (plane->color.x < 0 || plane->color.x > 255 ||
		plane->color.y < 0 || plane->color.y > 255 ||
		plane->color.z < 0 || plane->color.z > 255 ||
		plane->transperency > 1 || plane->reflect > 1)
		error_parab();
}

void	check_plane(t_obj *plane)
{
	if (plane->color.x < 0 || plane->color.x > 255 ||
		plane->color.y < 0 || plane->color.y > 255 ||
		plane->color.z < 0 || plane->color.z > 255 ||
		plane->transperency > 1 || plane->reflect > 1)
		error_plane();
}

void	check_sphere(t_obj *sphere)
{
	if (sphere->radius < 0.1 ||
		sphere->color.x < 0 || sphere->color.x > 255 ||
		sphere->color.y < 0 || sphere->color.y > 255 ||
		sphere->color.z < 0 || sphere->color.z > 255 ||
		sphere->transperency > 1 || sphere->reflect > 1)
		error_spere();
}
