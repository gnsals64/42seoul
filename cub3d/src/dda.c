/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 03:42:24 by hupa              #+#    #+#             */
/*   Updated: 2023/05/26 15:10:12 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	dda(t_data *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->cub.map[data->ray.map_y][data->ray.map_x] == '1')
			data->ray.hit = 1;
	}
	if (data->ray.side == 0)
		data->ray.perp_wall_dist = (data->ray.map_x - data->player.pos_x
				+ (1 - data->ray.step_x) / 2) / data->ray.raydir_x;
	else
		data->ray.perp_wall_dist = (data->ray.map_y - data->player.pos_y
				+ (1 - data->ray.step_y) / 2) / data->ray.raydir_y;
}
