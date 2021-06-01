/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:31:18 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/07 17:15:44 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	loop_for_image(t_rt *r)
{
	SDL_Event		event;
	const uint8_t	*keys;

	keys = SDL_GetKeyboardState(NULL);
	while (1)
	{
		SDL_PollEvent(&event);
		if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type && \
		SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
		{
			ft_clean(r);
			SDL_DestroyWindow(r->win);
			TTF_Quit();
			SDL_Quit();
			exit(0);
		}
		if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT] || \
		keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_DOWN] || \
		keys[SDL_SCANCODE_Q] || keys[SDL_SCANCODE_W] || \
		keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_Z] || \
		keys[SDL_SCANCODE_P] || keys[SDL_SCANCODE_B] ||
		keys[SDL_SCANCODE_M])
			for_keys(r, keys);
	}
}

void	ft_image(t_rt *r)
{
	for_menu(r);
	r->texture = SDL_CreateTextureFromSurface(r->ren, r->screen);
	SDL_RenderCopy(r->ren, r->texture, NULL, NULL);
	SDL_RenderPresent(r->ren);
	if (r->menu == 0)
		SDL_FreeSurface(r->screen);
	SDL_DestroyTexture(r->texture);
	loop_for_image(r);
}

void	loop_for_main(t_rt *r)
{
	int			run;
	SDL_Event	event;

	run = 1;
	while (run)
	{
		SDL_PollEvent(&event);
		run = 0;
		if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type && \
		SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
		{
			ft_clean(r);
			SDL_DestroyWindow(r->win);
			TTF_Quit();
			exit(0);
		}
	}
}

int		main(int argc, char **argv)
{
	t_rt			*r;
	SDL_Surface		*image;

	if (argc != 2)
		ft_put_error("Usage: ./RTv1 [path of file]");
	if (!(ft_strstr(argv[1], ".json")))
		ft_put_error("Wrong file type");
	if (!(r = (t_rt *)malloc(sizeof(t_rt))))
		ft_put_error("Allocation memory error");
	init_r(r);
	ft_parser(argv[1], r);
	ft_init(r);
	if ((image = SDL_LoadBMP("textures/hands.bmp")) == NULL)
		ft_put_error("Problem with load BMP");
	r->texture = SDL_CreateTextureFromSurface(r->ren, image);
	SDL_FreeSurface(image);
	SDL_RenderClear(r->ren);
	SDL_RenderCopy(r->ren, r->texture, NULL, NULL);
	SDL_DestroyTexture(r->texture);
	SDL_RenderPresent(r->ren);
	loop_for_main(r);
	threads(r);
	ft_image(r);
	return (0);
}
