/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_board.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:28:51 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/09 22:28:41 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		bord(t_rt *r, t_light *tmp)
{
	t_board board;

	board.x1 = r->obj[r->clos].center.x - r->obj[r->clos].radius;
	board.x2 = r->obj[r->clos].center.x + r->obj[r->clos].radius;
	board.y1 = r->obj[r->clos].center.y - r->obj[r->clos].radius;
	board.y2 = r->obj[r->clos].center.y + r->obj[r->clos].radius;
	board.z1 = r->obj[r->clos].center.z - r->obj[r->clos].radius;
	board.z2 = r->obj[r->clos].center.z + r->obj[r->clos].radius;
	if (ft_strequ(tmp->type, "point") && tmp->position.x >= board.x1\
		&& tmp->position.x <= board.x2 && tmp->position.y >= board.y1\
		&& tmp->position.y <= board.y2 && tmp->position.z >= board.z1\
		&& tmp->position.z <= board.z2)
		return (1);
	return (0);
}

t_rt	*ft_clean(t_rt *r)
{
	int i;

	i = -1;
	while (++i < r->count)
	{
		if (r->obj[i].tex != NULL)
		{
			free(r->obj[i].tex->pixels);
			SDL_FreeSurface(r->obj[i].tex->img);
			free(r->obj[i].tex);
		}
	}
	free((void**)(r->obj));
	r->obj = NULL;
	free((void**)(r->light));
	r->light = NULL;
	SDL_FreeSurface(r->screen);
	SDL_DestroyRenderer(r->ren);
	SDL_DestroyWindow(r->win);
	SDL_Quit();
	free(r);
	r = NULL;
	exit(0);
}

void	check_torus(t_obj *plane)
{
	if (plane->color.x < 0 || plane->color.x > 255 ||
		plane->color.y < 0 || plane->color.y > 255 ||
		plane->color.z < 0 || plane->color.z > 255 ||
		plane->transperency > 1 || plane->reflect > 1)
		error_tore();
}
