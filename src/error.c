/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:27:22 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/26 17:27:22 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		error_plane(void)
{
	write(1, "Wrong data for plane\n", 21);
	exit(1);
}

void		error_cone(void)
{
	write(1, "Wrong data for cone\n", 20);
	exit(1);
}

void		error_cyl(void)
{
	write(1, "Wrong data for cylinder\n", 24);
	exit(1);
}

void		error_parab(void)
{
	write(1, "Wrong data for paraboloid\n", 26);
	exit(1);
}

void		error_tore(void)
{
	write(1, "Wrong data for torus\n", 21);
	exit(1);
}
