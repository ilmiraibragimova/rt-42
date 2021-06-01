/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paraboloid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:23:45 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 17:01:10 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_param_parab1(t_rt *r, struct json_object *parsed_data)
{
	struct json_object	*normal1;
	struct json_object	*scale;

	json_object_object_get_ex(parsed_data, "scale", &scale);
	json_object_object_get_ex(parsed_data, "normal1", &normal1);
	if (normal1 == NULL)
		error_read();
	r->obj[r->count].rot.x = json_object_get_double\
(json_object_array_get_idx(normal1, 0));
	r->obj[r->count].rot.y = json_object_get_double\
(json_object_array_get_idx(normal1, 1));
	r->obj[r->count].rot.z = json_object_get_double\
(json_object_array_get_idx(normal1, 2));
	r->obj[r->count].scale2 = json_object_get_double(scale);
}

void	parse_param_paral(t_rt *r, struct json_object *parsed_data, char *key)
{
	struct json_object	*point;
	struct json_object	*color;

	parsed_data = json_object_object_get(parsed_data, key);
	json_object_object_get_ex(parsed_data, "point", &point);
	json_object_object_get_ex(parsed_data, "color: [red, green, blue]", &color);
	if (point == NULL || color == NULL)
		error_read();
	r->obj[r->count].center.x = json_object_get_double\
(json_object_array_get_idx(point, 0));
	r->obj[r->count].center.y = json_object_get_double\
(json_object_array_get_idx(point, 1));
	r->obj[r->count].center.z = json_object_get_double\
(json_object_array_get_idx(point, 2));
	r->obj[r->count].color.x = json_object_get_double\
(json_object_array_get_idx(color, 0));
	r->obj[r->count].color.y = json_object_get_double\
(json_object_array_get_idx(color, 1));
	r->obj[r->count].color.z = json_object_get_double\
(json_object_array_get_idx(color, 2));
	parse_param_parab1(r, parsed_data);
}

void	parse_parab1(t_rt *r, struct json_object *parsed_data, char *key)
{
	parse_param_paral(r, parsed_data, key);
	check_parab(&r->obj[r->count]);
	r->obj[r->count].name = "paraboloid";
	if (r->obj[r->count].flag_tex == 3)
		r->obj[r->count].tex = tex_new_bmp(&r->obj[r->count]);
	else
		r->obj[r->count].tex = NULL;
	r->count++;
}

int		ft_json_for_each_parab(struct json_object *parsed_data, t_rt *r)
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
		if (!(ft_strstr(key, "paraboloid")))
			ft_put_error("Wrong data name");
		parse_parab1(r, parsed_data, key);
		entry_nextkey = entrykey->next;
		entrykey = entry_nextkey;
	}
	return (0);
}

void	parse_paraboloid(t_rt *r, struct json_object *parsed_json)
{
	struct json_object	*parsed_data;

	parsed_data = json_object_object_get(parsed_json, "Paraboloid");
	ft_json_for_each_parab(parsed_data, r);
}
