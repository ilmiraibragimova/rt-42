/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 21:37:29 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 16:59:22 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_cube(t_obj *spere)
{
	if (spere->radius < 0.1 ||
		spere->color.x < 0 || spere->color.x > 255 ||
		spere->color.y < 0 || spere->color.y > 255 ||
		spere->color.z < 0 || spere->color.z > 255 ||
		spere->transperency > 0 || spere->reflect > 0)
	{
		write(1, "Wrong data for cube\n", 20);
		exit(1);
	}
}

void	parse_param_cube(t_rt *r, struct json_object *parsed_data, char *key)
{
	struct json_object *radius;
	struct json_object *color;
	struct json_object *trans;
	struct json_object *reflect;
	struct json_object *specular;

	parsed_data = json_object_object_get(parsed_data, key);
	json_object_object_get_ex(parsed_data, "radius", &radius);
	json_object_object_get_ex(parsed_data, "specular", &specular);
	json_object_object_get_ex(parsed_data, "reflection", &reflect);
	json_object_object_get_ex(parsed_data, "transperency", &trans);
	json_object_object_get_ex(parsed_data, "color: [red, green, blue]", &color);
	if (color == NULL)
		error_read();
	r->obj[r->count].radius = json_object_get_double(radius);
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

void	parse_cube1(t_rt *r, struct json_object *parsed_data, char *key)
{
	parse_param_cube(r, parsed_data, key);
	check_cube(&r->obj[r->count]);
	r->obj[r->count].name = "cube";
	if (r->obj[r->count].flag_tex == 3)
		r->obj[r->count].tex = tex_new_bmp(&r->obj[r->count]);
	else
		r->obj[r->count].tex = NULL;
	r->count++;
}

int		ft_json_for_each_cube(struct json_object *parsed_data, t_rt *r)
{
	struct lh_entry	*entry_nextkey;
	char			*key;
	struct lh_entry	*entrykey;

	entry_nextkey = NULL;
	key = NULL;
	entrykey = json_object_get_object(parsed_data)->head;
	while (entrykey)
	{
		key = (char *)lh_entry_k(entrykey);
		if (!(ft_strstr(key, "cube")))
			ft_put_error("Wrong data name");
		parse_cube1(r, parsed_data, key);
		entry_nextkey = entrykey->next;
		entrykey = entry_nextkey;
	}
	return (0);
}

void	parse_cube(t_rt *r, struct json_object *parsed_json)
{
	struct json_object *parsed_data;

	parsed_data = json_object_object_get(parsed_json, "Cubes");
	ft_json_for_each_cube(parsed_data, r);
}
