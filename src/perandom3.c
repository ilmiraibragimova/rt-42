/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perandom3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:07:02 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 21:21:19 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_perandom11(int perandom[])
{
	perandom[243] = 24;
	perandom[244] = 72;
	perandom[245] = 243;
	perandom[246] = 141;
	perandom[247] = 128;
	perandom[248] = 195;
	perandom[249] = 78;
	perandom[250] = 66;
	perandom[251] = 215;
	perandom[252] = 61;
	perandom[253] = 156;
	perandom[254] = 180;
	perandom[255] = 229;
}

void	init_perandom10(int perandom[])
{
	perandom[223] = 184;
	perandom[224] = 84;
	perandom[225] = 204;
	perandom[226] = 176;
	perandom[227] = 115;
	perandom[228] = 121;
	perandom[229] = 50;
	perandom[230] = 45;
	perandom[231] = 127;
	perandom[232] = 4;
	perandom[233] = 150;
	perandom[234] = 254;
	perandom[235] = 138;
	perandom[236] = 236;
	perandom[237] = 205;
	perandom[238] = 93;
	perandom[239] = 222;
	perandom[240] = 114;
	perandom[241] = 67;
	perandom[242] = 29;
	init_perandom11(perandom);
}

void	init_perlin(int perlin[])
{
	int i;
	int perandom[256];

	i = -1;
	init_perandom(perandom);
	while (++i < 256)
	{
		perlin[i] = perandom[i];
		perlin[256 + i] = perlin[i];
	}
}
