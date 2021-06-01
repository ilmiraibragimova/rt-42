/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:28:08 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/30 22:17:35 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		error_spere(void)
{
	write(1, "Wrong data for sphere\n", 22);
	exit(1);
}

void		error_open(void)
{
	write(1, "Wrong file\n", 11);
	exit(1);
}

void		error_read(void)
{
	write(1, "Wrong data format\n", 18);
	exit(1);
}

void		error_malloc(void)
{
	write(1, "Allocation error\n", 17);
	exit(1);
}

void		error_lite(void)
{
	write(1, "Wrong data for light\n", 21);
	exit(1);
}
