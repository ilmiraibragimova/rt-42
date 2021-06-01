/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:21:21 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 20:43:35 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*find_path_third(int p)
{
	char *s;

	s = NULL;
	if (p == 17)
		s = "textures/asphalt.bmp";
	else if (p == 18)
		s = "textures/panelki.bmp";
	else if (p == 19)
		s = "textures/panelka1.bmp";
	else if (p == 20)
		s = "textures/panelka2.bmp";
	else if (p == 21)
		s = "textures/panelka3.bmp";
	else if (p == 22)
		s = "textures/panelka4.bmp";
	else if (p == 23)
		s = "textures/sky.bmp";
	else if (p == 24)
		s = "textures/panelka5.bmp";
	else if (p == 25)
		s = "textures/twin.bmp";
	else
		ft_put_error("Wrong path for file");
	return (s);
}

char	*find_path_second(int p)
{
	char *s;

	s = NULL;
	if (p == 8)
		s = "textures/earth.bmp";
	else if (p == 9)
		s = "textures/mars.bmp";
	else if (p == 10)
		s = "textures/jupiter.bmp";
	else if (p == 11)
		s = "textures/saturn.bmp";
	else if (p == 12)
		s = "textures/uranus.bmp";
	else if (p == 13)
		s = "textures/neptune.bmp";
	else if (p == 14)
		s = "textures/column.bmp";
	else if (p == 15)
		s = "textures/rock.bmp";
	else if (p == 16)
		s = "textures/sundown.bmp";
	else
		return (find_path_third(p));
	return (s);
}

char	*find_path(int p)
{
	char *s;

	s = NULL;
	if (p == 0)
		s = "textures/sun.bmp";
	else if (p == 1)
		s = "textures/brick_base.bmp";
	else if (p == 2)
		s = "textures/stars.bmp";
	else if (p == 3)
		s = "textures/metal_floor_normal.bmp";
	else if (p == 4)
		s = "textures/bamboo_base.bmp";
	else if (p == 5)
		s = "textures/stained_glass_base.bmp";
	else if (p == 6)
		s = "textures/mercury.bmp";
	else if (p == 7)
		s = "textures/venus.bmp";
	else if (p == 101)
		s = "textures/water.bmp";
	else
		return (find_path_second(p));
	return (s);
}
