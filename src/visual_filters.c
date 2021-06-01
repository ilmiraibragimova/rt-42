/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_filters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 21:28:17 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 22:17:51 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sepia(t_rt *r)
{
	t_vec	example;

	example = r->obj[r->clos].color1;
	r->obj[r->clos].color1.x = example.x * 0.393\
	+ example.y * 0.769 + example.z * 0.189;
	r->obj[r->clos].color1.y = example.x * 0.349\
	+ example.y * 0.686 + example.z * 0.168;
	r->obj[r->clos].color1.z = example.x * 0.272\
	+ example.y * 0.534 + example.z * 0.131;
}

void	gray(t_rt *r)
{
	t_vec	example;

	example = r->obj[r->clos].color1;
	r->obj[r->clos].color1.x = example.x * 0.2126\
	+ example.y * 0.7152 + example.z * 0.0722;
	r->obj[r->clos].color1.y = example.x * 0.2126\
	+ example.y * 0.7152 + example.z * 0.0722;
	r->obj[r->clos].color1.z = example.x * 0.2126\
	+ example.y * 0.7152 + example.z * 0.0722;
}

void	invert(t_rt *r)
{
	t_vec	example;

	example = r->obj[r->clos].color1;
	r->obj[r->clos].color1.x = (1 + example.x / 255 * (-1)) * 255;
	r->obj[r->clos].color1.y = (1 + example.y / 255 * (-1)) * 255;
	r->obj[r->clos].color1.z = (1 + example.z / 255 * (-1)) * 255;
}

void	crazy(t_rt *r)
{
	t_vec	example;

	example = r->obj[r->clos].color1;
	r->obj[r->clos].color1.x = (0.213 + cos(0) * 0.787 - example.x) +
	(0.715 - cos(0) * 0.715 - example.y) + (0.072 - cos(0) * 0.072 + example.z);
	r->obj[r->clos].color1.y = (0.213 - cos(0) * 0.213 + example.x) +
	(0.715 + cos(0) * 0.285 + example.y) + (0.072 - cos(0) * 0.072 - example.z);
	r->obj[r->clos].color1.z = (0.213 - cos(0) * 0.213 - example.x) +
	(0.715 - cos(0) * 0.715 + example.y) + (0.072 + cos(0) * 0.928 + example.z);
}

void	effects(t_rt *r)
{
	if (r->filter == 1)
		sepia(r);
	else if (r->filter == 2)
		gray(r);
	else if (r->filter == 3)
		invert(r);
	else if (r->filter == 4)
		crazy(r);
}
