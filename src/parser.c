/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:53:59 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 12:03:54 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	counter_obj(t_rt *r, char *arg)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	if ((fd = open(arg, O_RDWR)) < 0)
		error_open();
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "cone") || ft_strstr(line, "sphere")
		|| ft_strstr(line, "plane") || ft_strstr(line, "cylinder") ||
			ft_strstr(line, "paraboloid") || ft_strstr(line, "torus") ||
			ft_strstr(line, "cube"))
			r->amount_obj++;
		if (ft_strstr(line, "light"))
			r->amount_ligth++;
		if (ft_strequ(line, "cam:"))
			i++;
		free(line);
	}
	close(fd);
}

void	init_obj1(t_obj *obj, int i)
{
	obj[i].p = (t_vec){0, 0, 0};
	obj[i].in = 0;
	obj[i].out = 0;
	obj[i].scale2 = 0;
	obj[i].flag_tex = 0;
	obj[i].t_w = 1;
	obj[i].t_h = 1;
	obj[i].t_col = 0;
	obj[i].shad = 0;
	obj[i].tex = NULL;
	obj[i].path = 0;
}

void	init_obj(t_obj *obj, int count)
{
	int i;

	i = -1;
	while (++i < count)
	{
		obj[i].reflect = 0;
		obj[i].transperency = 0;
		obj[i].specular = -1;
		obj[i].color = (t_vec) {0, 0, 0};
		obj[i].color1 = (t_vec) {0, 0, 0};
		obj[i].max = INFINITY;
		obj[i].min = 0;
		obj[i].limit1 = 1;
		obj[i].is_limit = 0;
		obj[i].radius = 0;
		obj[i].center = (t_vec) {0, 0, 0};
		obj[i].rot = (t_vec) {0, 0, 0};
		obj[i].n = (t_vec) {0, 0, 0};
		obj[i].limit = (t_vec) {0, 0, 0};
		obj[i].name = NULL;
		obj[i].t = 0;
		init_obj1(obj, i);
	}
}

void	init_light(t_light *light, int count)
{
	int i;

	i = -1;
	while (++i < count)
	{
		light[i].position = (t_vec){0, 0, 0};
		light[i].direction = (t_vec){0, 0, 0};
	}
}

void	ft_parser(char *arg, t_rt *r)
{
	counter_obj(r, arg);
	if (!(r->obj = ft_memalloc(sizeof(t_obj) * r->amount_obj)))
		error_malloc();
	if (!(r->light = (t_light *)malloc(sizeof(t_light) * r->amount_ligth)))
		error_malloc();
	init_obj(r->obj, r->amount_obj);
	init_light(r->light, r->amount_ligth);
	ft_json(arg, r);
}
