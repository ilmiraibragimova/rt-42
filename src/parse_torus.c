/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_torus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:49:38 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 17:19:21 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_param_torus1(t_rt *r, struct json_object *parsed_data)
{
	struct json_object *max;
	struct json_object *min;
	struct json_object *reflect;
	struct json_object *specular;
	struct json_object *color;

	json_object_object_get_ex(parsed_data, "max", &max);
	json_object_object_get_ex(parsed_data, "min", &min);
	json_object_object_get_ex(parsed_data, "specular", &specular);
	json_object_object_get_ex(parsed_data, "reflection", &reflect);
	json_object_object_get_ex(parsed_data, "color: [red, green, blue]", &color);
	if (color == NULL)
		error_read();
	r->obj[r->count].max = json_object_get_double(max);
	r->obj[r->count].min = json_object_get_double(min);
	r->obj[r->count].specular = json_object_get_double(specular);
	r->obj[r->count].reflect = json_object_get_double(reflect);
	r->obj[r->count].color.x = json_object_get_double\
(json_object_array_get_idx(color, 0));
	r->obj[r->count].color.y = json_object_get_double\
(json_object_array_get_idx(color, 1));
	r->obj[r->count].color.z = json_object_get_double\
(json_object_array_get_idx(color, 2));
}

void	parse_param_torus(t_rt *r, struct json_object *parsed_data, char *key)
{
	struct json_object *point;
	struct json_object *trans;
	struct json_object *rot;

	parsed_data = json_object_object_get(parsed_data, key);
	json_object_object_get_ex(parsed_data, "point", &point);
	json_object_object_get_ex(parsed_data, "rot", &rot);
	json_object_object_get_ex(parsed_data, "transperency", &trans);
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
	r->obj[r->count].transperency = json_object_get_double(trans);
	parse_param_torus1(r, parsed_data);
}

void	parse_torus1(t_rt *r, struct json_object *parsed_data, char *key)
{
	parse_param_torus(r, parsed_data, key);
	check_torus(&r->obj[r->count]);
	r->obj[r->count].name = "torus";
	if (r->obj[r->count].flag_tex == 3)
		r->obj[r->count].tex = tex_new_bmp(&r->obj[r->count]);
	else
		r->obj[r->count].tex = NULL;
	r->count++;
}

int		ft_json_for_each_torus(struct json_object *parsed_data, t_rt *r)
{
	struct lh_entry	*entry_nextkey;
	struct lh_entry	*entrykey;
	char			*key;

	entry_nextkey = NULL;
	key = NULL;
	entrykey = json_object_get_object(parsed_data)->head;
	while (entrykey)
	{
		key = (char *)lh_entry_k(entrykey);
		parse_torus1(r, parsed_data, key);
		entry_nextkey = entrykey->next;
		entrykey = entry_nextkey;
	}
	return (0);
}

void	parse_torus(t_rt *r, struct json_object *parsed_json)
{
	struct json_object	*parsed_data;

	parsed_data = json_object_object_get(parsed_json, "Torus");
	ft_json_for_each_torus(parsed_data, r);
}
