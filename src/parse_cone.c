/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:46:01 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 16:57:14 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_param_cone2(t_rt *r, struct json_object *parsed_data)
{
	struct json_object *is_limit;
	struct json_object *l;
	struct json_object *limit1;

	json_object_object_get_ex(parsed_data, "is_limit", &is_limit);
	json_object_object_get_ex(parsed_data, "limit", &l);
	json_object_object_get_ex(parsed_data, "size", &limit1);
	if (l == NULL)
		error_read();
	r->obj[r->count].limit.x = json_object_get_double\
(json_object_array_get_idx(l, 0));
	r->obj[r->count].limit.y = json_object_get_double\
(json_object_array_get_idx(l, 1));
	r->obj[r->count].limit.z = json_object_get_double\
(json_object_array_get_idx(l, 2));
	r->obj[r->count].is_limit = json_object_get_int(is_limit);
	r->obj[r->count].limit1 = json_object_get_double(limit1);
}

void	parse_param_cone1(t_rt *r, struct json_object *parsed_data)
{
	struct json_object	*color;
	struct json_object	*trans;
	struct json_object	*reflect;
	struct json_object	*specular;
	struct json_object	*radius;

	json_object_object_get_ex(parsed_data, "specular", &specular);
	json_object_object_get_ex(parsed_data, "radius", &radius);
	json_object_object_get_ex(parsed_data, "reflection", &reflect);
	json_object_object_get_ex(parsed_data, "transperency", &trans);
	json_object_object_get_ex(parsed_data, "color: [red, green, blue]", &color);
	if (color == NULL)
		error_read();
	ft_json_tex(r, parsed_data, "texture");
	r->obj[r->count].color.x = json_object_get_double\
(json_object_array_get_idx(color, 0));
	r->obj[r->count].color.y = json_object_get_double\
(json_object_array_get_idx(color, 1));
	r->obj[r->count].color.z = json_object_get_double\
(json_object_array_get_idx(color, 2));
	r->obj[r->count].specular = json_object_get_double(specular);
	r->obj[r->count].reflect = json_object_get_double(reflect);
	r->obj[r->count].transperency = json_object_get_double(trans);
	r->obj[r->count].radius = json_object_get_double(radius);
	parse_param_cone2(r, parsed_data);
}

void	parse_param_cone(t_rt *r, struct json_object *parsed_data, char *key)
{
	struct json_object	*point;
	struct json_object	*rot;

	parsed_data = json_object_object_get(parsed_data, key);
	json_object_object_get_ex(parsed_data, "point", &point);
	json_object_object_get_ex(parsed_data, "rot", &rot);
	if (point == NULL || rot == NULL)
		error_read();
	r->obj[r->count].center.x = json_object_get_double\
(json_object_array_get_idx(point, 0));
	r->obj[r->count].center.y = json_object_get_double\
(json_object_array_get_idx(point, 1));
	r->obj[r->count].center.z = json_object_get_double\
(json_object_array_get_idx(point, 2));
	r->obj[r->count].rot.x = json_object_get_double\
(json_object_array_get_idx(rot, 0));
	r->obj[r->count].rot.y = json_object_get_double\
(json_object_array_get_idx(rot, 1));
	r->obj[r->count].rot.z = json_object_get_double\
(json_object_array_get_idx(rot, 2));
	parse_param_cone1(r, parsed_data);
}

void	parse_cone1(t_rt *r, struct json_object *parsed_data, char *key)
{
	parse_param_cone(r, parsed_data, key);
	check_cone(&r->obj[r->count]);
	r->obj[r->count].rot = \
	rotate_vec(r->obj[r->count].rot, (t_vec){0, 1, 0});
	r->obj[r->count].name = "cone";
	if (r->obj[r->count].flag_tex == 3)
		r->obj[r->count].tex = tex_new_bmp(&r->obj[r->count]);
	else
		r->obj[r->count].tex = NULL;
	r->count++;
}

void	parse_cone(t_rt *r, struct json_object *parsed_json)
{
	struct json_object	*parsed_data;
	struct lh_entry		*entry_nextkey;
	char				*key;
	struct lh_entry		*entrykey;

	entry_nextkey = NULL;
	key = NULL;
	parsed_data = json_object_object_get(parsed_json, "Cones");
	entrykey = json_object_get_object(parsed_data)->head;
	while (entrykey)
	{
		key = (char *)lh_entry_k(entrykey);
		if (!(ft_strstr(key, "cone")))
			ft_put_error("Wrong data name");
		parse_cone1(r, parsed_data, key);
		entry_nextkey = entrykey->next;
		entrykey = entry_nextkey;
	}
}
