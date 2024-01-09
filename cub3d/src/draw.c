/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 03:39:55 by hupa              #+#    #+#             */
/*   Updated: 2023/05/26 16:33:00 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_raydir(t_data *data)
{
	if (data->ray.side == 1)
	{
		if (data->ray.raydir_y > 0)
			return (NO);
		else
			return (SO);
	}
	else
	{
		if (data->ray.raydir_x > 0)
			return (WE);
		else
			return (EA);
	}
}

void	check_drawing_range(t_data *data)
{
	data->ray.line_height = (int)(HEIGHT / data->ray.perp_wall_dist);
	data->ray.draw_start = -data->ray.line_height / 2 + HEIGHT / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height / 2 + HEIGHT / 2;
	if (data->ray.draw_end >= HEIGHT)
		data->ray.draw_end = HEIGHT - 1;
}

void	draw_all(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			data->img.addr[i * WIDTH + j] = data->tex.buf[i][j];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.mlx_win,
		data->img.img, 0, 0);
}

void	draw_ceiling_floor(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i > HEIGHT / 2)
				data->tex.buf[i][j] = data->cub.f_color;
			else
				data->tex.buf[i][j] = data->cub.c_color;
			j++;
		}
		i++;
	}
}
