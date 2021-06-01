/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:40:45 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/11 01:11:25 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_t		*tex_new_surface(SDL_Surface *s)
{
	t_t	*ret;
	int surface_size;

	if (!(ret = (t_t *)malloc(sizeof(t_t))))
		error_malloc();
	surface_size = s->w * s->h * s->format->BytesPerPixel;
	if (!(ret->pixels = malloc(sizeof(Uint32) * surface_size)))
		error_malloc();
	ft_memcpy(ret->pixels, s->pixels, surface_size);
	ret->img = s;
	ret->width = s->w;
	ret->height = s->h;
	ret->bytes_per_pixel = s->format->BytesPerPixel;
	ret->l_size = s->pitch;
	ret->size = ret->height * ret->l_size;
	ret->rmask = s->format->Rmask;
	ret->rshift = s->format->Rshift;
	ret->rloss = s->format->Rloss;
	ret->gmask = s->format->Gmask;
	ret->gshift = s->format->Gshift;
	ret->gloss = s->format->Gloss;
	ret->bmask = s->format->Bmask;
	ret->bshift = s->format->Bshift;
	ret->bloss = s->format->Bloss;
	return (ret);
}

t_t		*tex_new_bmp(t_obj *obj)
{
	char		*file;
	SDL_Surface	*s;

	file = find_path(obj->path);
	if ((s = SDL_LoadBMP(file)) == NULL)
		ft_put_error("Loading texture error");
	return (tex_new_surface(s));
}

Uint32	tex_get_pixel(t_t *tex, int x, int y)
{
	if (((y * tex->l_size) + (x * tex->bytes_per_pixel)) >\
	(tex->width * tex->height * tex->bytes_per_pixel) || \
	((y * tex->l_size) + (x * tex->bytes_per_pixel)) < 0)
		ft_put_error("Allocation error");
	return (*((unsigned int *)(tex->pixels +\
		((y * tex->l_size) + (x * tex->bytes_per_pixel)))));
}

t_vec	find_rgb(t_rt *r, double u_v[])
{
	Uint32			pixel;
	Uint8			color[3];
	Uint32			temp;

	pixel = tex_get_pixel(r->obj[r->clos].tex, u_v[0], u_v[1]);
	temp = pixel & r->obj[r->clos].tex->rmask;
	temp = temp >> r->obj[r->clos].tex->rshift;
	temp = temp << r->obj[r->clos].tex->rloss;
	color[0] = (Uint8)temp;
	temp = pixel & r->obj[r->clos].tex->gmask;
	temp = temp >> r->obj[r->clos].tex->gshift;
	temp = temp << r->obj[r->clos].tex->gloss;
	color[1] = (Uint8)temp;
	temp = pixel & r->obj[r->clos].tex->bmask;
	temp = temp >> r->obj[r->clos].tex->bshift;
	temp = temp << r->obj[r->clos].tex->bloss;
	color[2] = (Uint8)temp;
	return (t_vec){color[0], color[1], color[2]};
}

t_vec	calculate_texture_color(t_rt *r)
{
	double u_v[2];

	if (r->obj[r->clos].tex != NULL)
	{
		spherical_map(r->obj[r->clos].p, r, u_v);
		u_v[0] *= (r->obj[r->clos].tex->width - 1) *
				(r->obj[r->clos].t_h);
		u_v[1] *= (r->obj[r->clos].tex->height - 1) *
				(r->obj[r->clos].t_w);
		u_v[0] = (int)(u_v[0] + r->obj[r->clos].t_h) %
				(r->obj[r->clos].tex->width);
		u_v[1] = (int)(u_v[1] + r->obj[r->clos].t_w) %
				(r->obj[r->clos].tex->height);
		return (find_rgb(r, u_v));
	}
	else
	{
		ft_put_error("wrong data for texture");
		return ((t_vec) {0, 0, 0});
	}
}
