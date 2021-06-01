/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:37:05 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 17:32:07 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_param_sphere1(t_rt *r, struct json_object *parsed_data)
{
	struct json_object *color;
	struct json_object *trans;
	struct json_object *reflect;
	struct json_object *specular;

	json_object_object_get_ex(parsed_data, "specular", &specular);
	json_object_object_get_ex(parsed_data, "reflection", &reflect);
	json_object_object_get_ex(parsed_data, "transperency", &trans);
	json_object_object_get_ex(parsed_data, "color: [red, green, blue]", &color);
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
}

void	parse_param_sphere(t_rt *r, \
	struct json_object *parsed_data, char *key)
{
	struct json_object *point;
	struct json_object *radius;

	parsed_data = json_object_object_get(parsed_data, key);
	json_object_object_get_ex(parsed_data, "point", &point);
	json_object_object_get_ex(parsed_data, "radius", &radius);
	if (point == NULL)
		error_read();
	ft_json_tex(r, parsed_data, "texture");
	r->obj[r->count].center.x = json_object_get_double\
(json_object_array_get_idx(point, 0));
	r->obj[r->count].center.y = json_object_get_double\
(json_object_array_get_idx(point, 1));
	r->obj[r->count].center.z = json_object_get_double\
(json_object_array_get_idx(point, 2));
	r->obj[r->count].radius = json_object_get_double(radius);
	parse_param_sphere1(r, parsed_data);
}

void	parse_sphere1(t_rt *r, struct json_object *parsed_data, char *key)
{
	parse_param_sphere(r, parsed_data, key);
	check_sphere(&r->obj[r->count]);
	r->obj[r->count].name = "sphere";
	if (r->obj[r->count].flag_tex == 3)
		r->obj[r->count].tex = tex_new_bmp(&r->obj[r->count]);
	else
		r->obj[r->count].tex = NULL;
	r->count++;
}

int		ft_json_for_each_sphere(struct json_object *parsed_data, t_rt *r)
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
		if (!(ft_strstr(key, "sphere")))
			ft_put_error("Wrong data name");
		parse_sphere1(r, parsed_data, key);
		entry_nextkey = entrykey->next;
		entrykey = entry_nextkey;
	}
	return (0);
}

void	parse_sphere(t_rt *r, struct json_object *parsed_json)
{
	struct json_object	*parsed_data;

	parsed_data = json_object_object_get(parsed_json, "Spheres");
	ft_json_for_each_sphere(parsed_data, r);
}
