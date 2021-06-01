/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:14:49 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/12 16:59:22 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_light(t_light light)
{
	if (light.intensity > 1 || light.intensity < 0)
		error_lite();
	if (ft_strequ("ambient", light.type))
		return ;
	else if (ft_strequ("point", light.type))
		return ;
	else if (ft_strequ("direction", light.type))
		return ;
	else
		error_lite();
}

void	parse_param_light1(t_rt *r, struct json_object *parsed_data)
{
	struct json_object *intensity;
	struct json_object *light_type;

	json_object_object_get_ex(parsed_data, "intensity", &intensity);
	json_object_object_get_ex(parsed_data, "type", &light_type);
	r->light[r->l].intensity = json_object_get_double(intensity);
	r->light[r->l].type = (char*)json_object_get_string(light_type);
}

void	parse_param_light(t_rt *r, struct json_object *parsed_data, char *key)
{
	struct json_object *point;
	struct json_object *direction;
	struct json_object *parsed_data1;

	parsed_data1 = json_object_object_get(parsed_data, key);
	json_object_object_get_ex(parsed_data1, "point", &point);
	json_object_object_get_ex(parsed_data1, "direction", &direction);
	if (point == NULL || direction == NULL)
		error_read();
	r->light[r->l].position.x = json_object_get_double\
(json_object_array_get_idx(point, 0));
	r->light[r->l].position.y = json_object_get_double\
(json_object_array_get_idx(point, 1));
	r->light[r->l].position.z = json_object_get_double\
(json_object_array_get_idx(point, 2));
	r->light[r->l].direction.x = json_object_get_double\
(json_object_array_get_idx(direction, 0));
	r->light[r->l].direction.y = json_object_get_double\
(json_object_array_get_idx(direction, 1));
	r->light[r->l].direction.z = json_object_get_double\
(json_object_array_get_idx(direction, 2));
	parse_param_light1(r, parsed_data1);
}

void	parse_light1(t_rt *r, struct json_object *parsed_data, char *key)
{
	parse_param_light(r, parsed_data, key);
	check_light(r->light[r->l]);
	r->l++;
}

void	parse_light(struct json_object *parsed_json, t_rt *r, char *key1)
{
	struct json_object	*parsed_data;
	struct lh_entry		*entry_nextkey;
	struct lh_entry		*entrykey;
	char				*key;

	entry_nextkey = NULL;
	key = NULL;
	parsed_data = json_object_object_get(parsed_json, key1);
	entrykey = json_object_get_object(parsed_data)->head;
	while (entrykey)
	{
		key = (char *)lh_entry_k(entrykey);
		if (!(ft_strstr(key, "light")))
			ft_put_error("Wrong data name");
		parse_light1(r, parsed_data, key);
		entry_nextkey = entrykey->next;
		entrykey = entry_nextkey;
	}
}
