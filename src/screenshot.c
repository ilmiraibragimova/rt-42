/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 21:24:02 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 21:24:02 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_check(const char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) && fd == -1)
		return (-1);
	close(fd);
	return (0);
}

char	*screenshot_name(int num)
{
	char	*name;
	char	*n;
	int		i;

	n = ft_itoa(num);
	name = ft_strdup("My_screenshot0000.bmp");
	i = 0;
	while (n[i])
	{
		name[17 - ft_strlen(n) + i] = n[i];
		i++;
	}
	free(n);
	return (name);
}

char	*name_screenshot(void)
{
	int		i;
	char	*name;

	i = 1;
	while (i <= 500)
	{
		name = screenshot_name(i);
		if (ft_check(name) == -1)
			return (name);
		else
			free(name);
		i++;
	}
	return (ft_strdup("My_screenshot.bmp"));
}

int		screenshot(t_rt *r)
{
	t_screenshot	screenshot1;

	screenshot1.surface = NULL;
	screenshot1.ren = NULL;
	screenshot1.name = NULL;
	screenshot1.win_size = (SDL_Rect){0, 0, WIDTH, HEIGHT};
	screenshot1.ren = r->ren;
	if ((screenshot1.surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32,\
	0, 0, 0, 0)) == NULL)
		ft_put_error("error");
	if (SDL_RenderReadPixels(screenshot1.ren, &screenshot1.win_size,\
		SDL_GetWindowPixelFormat(r->win),\
		screenshot1.surface->pixels, screenshot1.surface->pitch) != 0)
		ft_put_error("Screenshot error");
	screenshot1.name = name_screenshot();
	if (SDL_SaveBMP(screenshot1.surface, screenshot1.name) != 0)
		ft_put_error("Screenshot error");
	free(screenshot1.name);
	SDL_FreeSurface(screenshot1.surface);
	return (0);
}
