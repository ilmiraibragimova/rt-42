/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:31:18 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/07 17:15:44 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	menu_fourth(t_rt *r, SDL_Color text_color, TTF_Font *verdana_font)
{
	SDL_Surface	*text_surface;

	text_surface = TTF_RenderText_Solid(verdana_font, \
		"Stereoscopy: P", text_color);
	r->texture = SDL_CreateTextureFromSurface(r->ren, text_surface);
	take_rect(r, 5, 120);
	SDL_FreeSurface(text_surface);
	text_surface = TTF_RenderText_Solid(verdana_font, \
		"Exit: Esc/[X]", text_color);
	r->texture = SDL_CreateTextureFromSurface(r->ren, text_surface);
	take_rect(r, 5, 140);
	SDL_FreeSurface(text_surface);
}

void	menu_third(t_rt *r, SDL_Color text_color, TTF_Font *verdana_font)
{
	SDL_Surface	*text_surface;

	text_surface = TTF_RenderText_Solid(verdana_font, \
	"Color filter: Z", text_color);
	r->texture = SDL_CreateTextureFromSurface(r->ren, text_surface);
	take_rect(r, 5, 80);
	SDL_FreeSurface(text_surface);
	text_surface = TTF_RenderText_Solid(verdana_font, "Blur: B", text_color);
	r->texture = SDL_CreateTextureFromSurface(r->ren, text_surface);
	take_rect(r, 5, 100);
	SDL_FreeSurface(text_surface);
	menu_fourth(r, text_color, verdana_font);
}

void	menu_second(t_rt *r, SDL_Color text_color, TTF_Font *verdana_font)
{
	SDL_Surface	*text_surface;

	text_surface = TTF_RenderText_Solid(verdana_font, "+/-: W/Q", text_color);
	r->texture = SDL_CreateTextureFromSurface(r->ren, text_surface);
	take_rect(r, 5, 40);
	SDL_FreeSurface(text_surface);
	text_surface = TTF_RenderText_Solid(verdana_font, \
	"Screenshot: S", text_color);
	r->texture = SDL_CreateTextureFromSurface(r->ren, text_surface);
	take_rect(r, 5, 60);
	SDL_FreeSurface(text_surface);
	menu_third(r, text_color, verdana_font);
}

void	menu_first(t_rt *r, SDL_Color text_color, TTF_Font *verdana_font)
{
	SDL_Surface	*text_surface;

	text_surface = TTF_RenderText_Solid(verdana_font, "MENU", text_color);
	r->texture = SDL_CreateTextureFromSurface(r->ren, text_surface);
	take_rect(r, 5, 0);
	SDL_FreeSurface(text_surface);
	text_surface = TTF_RenderText_Solid(verdana_font, \
	"Move: arrays", text_color);
	r->texture = SDL_CreateTextureFromSurface(r->ren, text_surface);
	take_rect(r, 5, 20);
	SDL_FreeSurface(text_surface);
	menu_second(r, text_color, verdana_font);
}

void	menu(t_rt *r)
{
	TTF_Font	*verdana_font;
	SDL_Surface	*image;

	if ((image = SDL_LoadBMP("textures/gray.bmp")) == NULL)
		ft_put_error("Problem with load BMP");
	r->texture = SDL_CreateTextureFromSurface(r->ren, image);
	take_rect_for_long_menu(r);
	SDL_FreeSurface(image);
	if ((verdana_font = TTF_OpenFont("textures/Verdana.ttf", 15)) == NULL)
		ft_put_error("Problem with open font");
	menu_first(r, take_color(), verdana_font);
	TTF_CloseFont(verdana_font);
}
