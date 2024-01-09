/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 03:29:22 by hupa              #+#    #+#             */
/*   Updated: 2023/05/26 15:11:31 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_raydir(t_data *data, int x)
{
	(void)x;
	if (data->ray.raydir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.pos_x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.pos_x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.raydir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.pos_y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.pos_y)
			* data->ray.delta_dist_y;
	}
}

void	init_ray(t_data *data, int x)
{
	data->ray.camera_x = 2 * x / (double)WIDTH - 1;
	data->ray.raydir_x = data->player.dir_x + data->player.plane_x
		* data->ray.camera_x;
	data->ray.raydir_y = data->player.dir_y + data->player.plane_y
		* data->ray.camera_x;
	data->ray.map_x = (int)data->player.pos_x;
	data->ray.map_y = (int)data->player.pos_y;
	data->ray.delta_dist_x = fabs(1 / data->ray.raydir_x);
	data->ray.delta_dist_y = fabs(1 / data->ray.raydir_y);
	data->ray.hit = 0;
	set_raydir(data, x);
}
