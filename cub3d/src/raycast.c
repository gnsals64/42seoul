/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 03:14:50 by hupa              #+#    #+#             */
/*   Updated: 2023/05/26 16:39:02 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	raycast(t_data *data)
{
	int	x;

	x = 0;
	draw_ceiling_floor(data);
	while (x < WIDTH)
	{
		init_ray(data, x);
		dda(data);
		check_drawing_range(data);
		check_drawing_point(data);
		cpy_buf(data, x);
		x++;
	}
}

void	cpy_buf(t_data *data, int x)
{
	int	y;
	int	color;

	y = data->ray.draw_start;
	while (y < data->ray.draw_end)
	{
		data->ray.tex_y = (int)data->ray.tex_pos & (TEX_H - 1);
		data->ray.tex_pos += data->ray.step;
		color = data->tex.tex[data->ray.texnum][TEX_H
			* data->ray.tex_y + data->ray.tex_x];
		data->tex.buf[y][x] = color;
		y++;
	}
}

void	check_drawing_point(t_data *data)
{
	data->ray.texnum = check_raydir(data);
	if (data->ray.side == 0)
		data->ray.wall_x = -(data->player.pos_y + data->ray.perp_wall_dist
				* data->ray.raydir_y);
	else
		data->ray.wall_x = -(data->player.pos_x + data->ray.perp_wall_dist
				* data->ray.raydir_x);
	data->ray.wall_x -= floor(data->ray.wall_x);
	data->ray.tex_x = (int)(data->ray.wall_x * (double)TEX_W);
	if (data->ray.side == 0 && data->ray.raydir_x > 0)
		data->ray.tex_x = TEX_W - data->ray.tex_x - 1;
	if (data->ray.side == 1 && data->ray.raydir_y < 0)
		data->ray.tex_x = TEX_W - data->ray.tex_x - 1;
	data->ray.step = 1.0 * TEX_H / data->ray.line_height;
	data->ray.tex_pos = (data->ray.draw_start - HEIGHT / 2
			+ data->ray.line_height / 2) * data->ray.step;
}
