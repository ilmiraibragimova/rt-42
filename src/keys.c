/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:19:21 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/26 17:26:19 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	key(t_rt *r, const uint8_t *keys)
{
	if (keys[SDL_SCANCODE_S])
		screenshot(r);
	if (keys[SDL_SCANCODE_Z])
		r->filter = r->filter < 4 ? r->filter + 1 : 0;
	if (keys[SDL_SCANCODE_B])
		r->blur = r->blur < 1 ? r->blur + 1 : 0;
	if (keys[SDL_SCANCODE_P])
		r->stereoscopy = r->stereoscopy < 1 ? r->stereoscopy + 1 : 0;
	if (keys[SDL_SCANCODE_M])
		r->menu = r->menu < 1 ? r->menu + 1 : 0;
}

void	rotate_cam(t_rt *r, const uint8_t *keys)
{
	if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT])
	{
		r->cam.point.x = keys[SDL_SCANCODE_LEFT] ? \
		r->cam.point.x - 0.5 : r->cam.point.x + 0.5;
		r->per_data.x_per += keys[SDL_SCANCODE_LEFT] ? \
		-0.5 : 0.5;
	}
	if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_DOWN])
	{
		r->cam.point.y = keys[SDL_SCANCODE_UP] ? \
		r->cam.point.y - 0.5 : r->cam.point.y + 0.5;
		r->per_data.y_per += keys[SDL_SCANCODE_LEFT] ? \
		-0.5 : 0.5;
	}
	if (keys[SDL_SCANCODE_Q] || keys[SDL_SCANCODE_W])
	{
		r->cam.point.z = keys[SDL_SCANCODE_Q] ? \
		r->cam.point.z - 0.5 : r->cam.point.z + 0.5;
		r->per_data.z_per += keys[SDL_SCANCODE_LEFT] ? \
		-0.5 : 0.5;
	}
	key(r, keys);
}

void	for_keys(t_rt *r, const uint8_t *keys)
{
	rotate_cam(r, keys);
	threads(r);
	if (r->menu)
		menu(r);
	else
	{
		for_menu(r);
		r->texture = SDL_CreateTextureFromSurface(r->ren, r->screen);
		SDL_FreeSurface(r->screen);
		SDL_RenderCopy(r->ren, r->texture, NULL, NULL);
		SDL_DestroyTexture(r->texture);
	}
	SDL_RenderPresent(r->ren);
}
