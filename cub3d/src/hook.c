/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:27:39 by hupa              #+#    #+#             */
/*   Updated: 2023/05/26 16:09:08 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	keypress_right(t_data *data)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = data->player.dir_x;
	oldplane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(data->player.rot_speed) \
		- data->player.dir_y * sin(data->player.rot_speed);
	data->player.dir_y = olddir_x * sin(data->player.rot_speed) \
		+ data->player.dir_y * cos(data->player.rot_speed);
	data->player.plane_x = data->player.plane_x * cos(data->player.rot_speed) \
		- data->player.plane_y * sin(data->player.rot_speed);
	data->player.plane_y = oldplane_x * sin(data->player.rot_speed) \
		+ data->player.plane_y * cos(data->player.rot_speed);
}

static void	keypress_left(t_data *data)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = data->player.dir_x;
	oldplane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(-data->player.rot_speed) \
		- data->player.dir_y * sin(-data->player.rot_speed);
	data->player.dir_y = olddir_x * sin(-data->player.rot_speed) \
		+ data->player.dir_y * cos(-data->player.rot_speed);
	data->player.plane_x = data->player.plane_x * cos(-data->player.rot_speed) \
		- data->player.plane_y * sin(-data->player.rot_speed);
	data->player.plane_y = oldplane_x * sin(-data->player.rot_speed) \
		+ data->player.plane_y * cos(-data->player.rot_speed);
}

int	key_press(int key, t_data *data)
{
	if (key == KEY_W)
		key_w(data);
	else if (key == KEY_S)
		key_s(data);
	else if (key == KEY_A)
		key_a(data);
	else if (key == KEY_D)
		key_d(data);
	else if (key == KEY_RIGHT)
		keypress_right(data);
	else if (key == KEY_LEFT)
		keypress_left(data);
	else if (key == KEY_ESC)
		key_exit(data);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	main_loop(data);
	return (0);
}
