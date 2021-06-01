/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:35:52 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/03 01:03:00 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_check_cam(t_vec angles)
{
	if (angles.x > 360 || angles.y > 360 || angles.z > 360)
	{
		write(1, "Camera data is wrong\n", 21);
		exit(1);
	}
}

void	parse_cam(struct json_object *parsed_json, t_rt *r)
{
	struct json_object	*point;
	struct json_object	*angle;
	struct json_object	*parsed_data;

	parsed_data = json_object_object_get(parsed_json, "Cam");
	json_object_object_get_ex(parsed_data, "point", &point);
	json_object_object_get_ex(parsed_data, "angle", &angle);
	if (point == NULL || angle == NULL)
		error_read();
	r->cam.point.x = \
		json_object_get_double(json_object_array_get_idx(point, 0));
	r->cam.point.y = \
		json_object_get_double(json_object_array_get_idx(point, 1));
	r->cam.point.z = \
		json_object_get_double(json_object_array_get_idx(point, 2));
	r->cam.angles.x = \
		json_object_get_double(json_object_array_get_idx(angle, 0));
	r->cam.angles.y = \
		json_object_get_double(json_object_array_get_idx(angle, 1));
	r->cam.angles.z = \
		json_object_get_double(json_object_array_get_idx(angle, 2));
	ft_check_cam(r->cam.angles);
}
