/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 21:43:11 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 20:45:44 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_param_cyl2(t_rt *r, struct json_object *parsed_data)
{
	struct json_object *max;
	struct json_object *min;
	struct json_object *is_limit;
	struct json_object *limit1;

	json_object_object_get_ex(parsed_data, "is_limit", &is_limit);
	json_object_object_get_ex(parsed_data, "size", &limit1);
	json_object_object_get_ex(parsed_data, "max", &max);
	json_object_object_get_ex(parsed_data, "min", &min);
	r->obj[r->count].max = json_object_get_double(max);
	r->obj[r->count].min = json_object_get_double(min);
	r->obj[r->count].is_limit = json_object_get_int(is_limit);
	r->obj[r->count].limit1 = json_object_get_double(limit1);
}

void	parse_param_cyl1(t_rt *r, struct json_object *parsed_data)
{
	struct json_object *color;
	struct json_object *trans;
	struct json_object *reflect;
	struct json_object *specular;
	struct json_object *radius;

	json_object_object_get_ex(parsed_data, "specular", &specular);
	json_object_object_get_ex(parsed_data, "radius", &radius);
	json_object_object_get_ex(parsed_data, "reflection", &reflect);
	json_object_object_get_ex(parsed_data, "transperency", &trans);
	json_object_object_get_ex(parsed_data, "color: [red, green, blue]", &color);
	ft_json_tex(r, parsed_data, "texture");
	if (color == NULL)
		error_read();
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
	parse_param_cyl2(r, parsed_data);
}

void	parse_param_cyl(t_rt *r, struct json_object *parsed_data, char *key)
{
	struct json_object *point;
	struct json_object *rot;

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
	parse_param_cyl1(r, parsed_data);
}

void	parse_cyl1(t_rt *r, struct json_object *parsed_data, char *key)
{
	parse_param_cyl(r, parsed_data, key);
	check_cylinder(&r->obj[r->count]);
	r->obj[r->count].rot = rotate_vec(r->obj[r->count].rot,\
	(t_vec){0, 1, 0});
	r->obj[r->count].name = "cylinder";
	if (r->obj[r->count].flag_tex == 3)
		r->obj[r->count].tex = tex_new_bmp(&r->obj[r->count]);
	else
		r->obj[r->count].tex = NULL;
	r->count++;
}

void	parse_cylinder(t_rt *r, struct json_object *parsed_json)
{
	struct json_object	*parsed_data;
	struct lh_entry		*entry_nextkey;
	char				*key;
	struct lh_entry		*entrykey;

	entry_nextkey = NULL;
	key = NULL;
	parsed_data = json_object_object_get(parsed_json, "Cylinders");
	entrykey = json_object_get_object(parsed_data)->head;
	while (entrykey)
	{
		key = (char *)lh_entry_k(entrykey);
		if (!(ft_strstr(key, "cylinder")))
			ft_put_error("Wrong data name");
		parse_cyl1(r, parsed_data, key);
		entry_nextkey = entrykey->next;
		entrykey = entry_nextkey;
	}
}
