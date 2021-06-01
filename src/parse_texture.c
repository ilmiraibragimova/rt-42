/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:42:39 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 18:31:26 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_json_tex1(t_rt *r, struct json_object *parsed_data)
{
	struct json_object *path;

	json_object_object_get_ex(parsed_data, "path", &path);
	r->obj[r->count].path = json_object_get_int(path);
}

void	ft_json_tex(t_rt *r, struct json_object *parsed_json, char *key)
{
	struct json_object *parsed_data;
	struct json_object *flag;
	struct json_object *h;
	struct json_object *w;
	struct json_object *col;

	parsed_data = json_object_object_get(parsed_json, key);
	json_object_object_get_ex(parsed_data, "flag", &flag);
	json_object_object_get_ex(parsed_data, "tex height", &h);
	json_object_object_get_ex(parsed_data, "tex wight", &w);
	json_object_object_get_ex(parsed_data, "tex.color", &col);
	r->obj[r->count].flag_tex = json_object_get_int(flag);
	r->obj[r->count].t_h = json_object_get_int(h);
	r->obj[r->count].t_w = json_object_get_int(w);
	r->obj[r->count].t_col = json_object_get_int(col);
	ft_json_tex1(r, parsed_data);
}
