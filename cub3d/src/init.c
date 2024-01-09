/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:40:46 by hupa              #+#    #+#             */
/*   Updated: 2023/05/26 16:00:12 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	ft_init_mlx(t_data *data)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "cub3d");
	data->mlx = mlx;
}

static void	ft_init_player(t_data *data)
{
	t_player	player;

	player.pos_x = -1;
	player.pos_y = -1;
	player.dir_x = 0.0;
	player.dir_y = 0.0;
	player.plane_x = 0.0;
	player.plane_y = 0.0;
	player.move_speed = 0.05;
	player.rot_speed = 0.05;
	player.player_size = PLAYER_SIZE;
	data->player = player;
}

static void	ft_init_cub(t_data *data)
{
	t_cub	cub;
	int		i;

	i = 0;
	cub.map = NULL;
	while (i < 4)
		cub.texture[i++] = NULL;
	cub.f_color = 0;
	cub.c_color = 0;
	cub.map_width = 0;
	cub.map_height = 0;
	cub.player = 0;
	data->cub = cub;
}

void	ft_init(t_data *data, char *av)
{
	ft_init_mlx(data);
	ft_init_player(data);
	ft_init_cub(data);
	parser(av, &data->cub, data);
	ft_init_tex(data);
	load_texture(data);
	ft_init_img(data);
	ft_init_buf(data);
}
