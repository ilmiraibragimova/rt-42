/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:53:55 by ilmira            #+#    #+#             */
/*   Updated: 2021/04/10 16:16:29 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_json1(char *key, t_rt *r, struct json_object *parsed_json)
{
	if (ft_strequ(key, "Cam"))
		parse_cam(parsed_json, r);
	else if (ft_strequ(key, "Lights"))
		parse_light(parsed_json, r, key);
	else if (ft_strequ(key, "Spheres"))
		parse_sphere(r, parsed_json);
	else if (ft_strequ(key, "Cones"))
		parse_cone(r, parsed_json);
	else if (ft_strequ(key, "Paraboloid"))
		parse_paraboloid(r, parsed_json);
	else if (ft_strequ(key, "Torus"))
		parse_torus(r, parsed_json);
	else if (ft_strequ(key, "Cubes"))
		parse_cube(r, parsed_json);
	else if (ft_strequ(key, "Planes"))
		parse_plane(r, parsed_json);
	else if (ft_strequ(key, "Cylinders"))
		parse_cylinder(r, parsed_json);
	else
		error_read();
}

void	ft_json_for_each(struct json_object	*parsed_json, t_rt *r)
{
	struct lh_entry		*entry_nextkey;
	char				*key;
	struct lh_entry		*entrykey;

	entry_nextkey = NULL;
	key = NULL;
	entrykey = json_object_get_object(parsed_json)->head;
	while (entrykey)
	{
		key = (char *)lh_entry_k(entrykey);
		ft_json1(key, r, parsed_json);
		entry_nextkey = entrykey->next;
		entrykey = entry_nextkey;
	}
}

void	ft_json(char *s, t_rt *r)
{
	int					fd;
	char				buffer[9000];
	struct json_object	*parsed_json;

	if ((fd = open(s, O_RDWR)) < 0)
		error_open();
	if (read(fd, buffer, 9000) < 0)
	{
		close(fd);
		error_read();
	}
	close(fd);
	if (!(parsed_json = json_tokener_parse(buffer)))
		error_open();
	ft_json_for_each(parsed_json, r);
	if (parsed_json != NULL)
		free(parsed_json);
}
