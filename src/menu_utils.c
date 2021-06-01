/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:31:18 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/07 17:15:44 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		take_rect(t_rt *r, int a, int b)
{
	int			texw;
	int			texh;
	SDL_Rect	dstrect;

	texw = 10;
	texh = 10;
	SDL_QueryTexture(r->texture, NULL, NULL, &texw, &texh);
	dstrect.x = a;
	dstrect.y = b;
	dstrect.w = texw;
	dstrect.h = texh;
	SDL_RenderCopy(r->ren, r->texture, NULL, &dstrect);
	SDL_DestroyTexture(r->texture);
}

SDL_Color	take_color(void)
{
	SDL_Color	text_color;

	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	text_color.a = 255;
	return (text_color);
}

void		take_rect_for_short_menu(t_rt *r)
{
	SDL_Rect dstrect;

	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 80;
	dstrect.h = 20;
	SDL_RenderCopy(r->ren, r->texture, NULL, &dstrect);
	SDL_DestroyTexture(r->texture);
}

void		take_rect_for_long_menu(t_rt *r)
{
	SDL_Rect dstrect;

	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 125;
	dstrect.h = 170;
	SDL_RenderCopy(r->ren, r->texture, NULL, &dstrect);
	SDL_DestroyTexture(r->texture);
}

void		for_menu(t_rt *r)
{
	int			texw;
	int			texh;
	SDL_Surface	*image;
	TTF_Font	*verdana_font;

	texw = 10;
	texh = 10;
	if ((image = SDL_LoadBMP("textures/gray.bmp")) == NULL)
		ft_put_error("Problem with load BMP");
	r->texture = SDL_CreateTextureFromSurface(r->ren, image);
	take_rect_for_short_menu(r);
	SDL_FreeSurface(image);
	if ((verdana_font = TTF_OpenFont("textures/Verdana.ttf", 15)) == NULL)
		ft_put_error("Problem with open font");
	image = TTF_RenderText_Solid(verdana_font,
		"MENU: M", take_color());
	r->texture = SDL_CreateTextureFromSurface(r->ren, image);
	SDL_QueryTexture(r->texture, NULL, NULL, &texw, &texh);
	take_rect(r, 5, 0);
	SDL_FreeSurface(image);
	TTF_CloseFont(verdana_font);
}
