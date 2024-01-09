/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:08:22 by hunaprk           #+#    #+#             */
/*   Updated: 2023/05/26 16:39:41 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../GNL/get_next_line.h"
# include "structs.h"
# include "util.h"
# include "parser.h"
# include <mlx.h>
# include <string.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <err.h>
# include <errno.h>
# include <fcntl.h>

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17

# define KEY_ESC 53
# define KEY_A 0
# define KEY_D 2
# define KEY_W 13
# define KEY_S 1
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define WIDTH 1280
# define HEIGHT 720
# define MINI_SCALE 1
# define TEX_H 64
# define TEX_W 64
# define PLAYER_SIZE 10

//init
void	ft_init(t_data *data, char *av);

//hook
int		key_press(int key, t_data *data);

//loop
int		main_loop(t_data *data);
void	loop(t_data *data);

//init_raycast
void	init_ray(t_data *data, int x);
void	set_raydir(t_data *data, int x);

//raycast
void	raycast(t_data *data);
void	cpy_buf(t_data *data, int x);
void	draw_all(t_data *data);

//dda
void	dda(t_data *data);

//draw
int		check_raydir(t_data *data);
void	check_drawing_range(t_data *data);
void	check_drawing_point(t_data *data);
void	draw_all(t_data *data);
void	draw_ceiling_floor(t_data *data);

//init_image
void	ft_init_img(t_data *data);
void	ft_init_buf(t_data *data);
void	ft_init_tex(t_data *data);
void	load_texture(t_data *data);
void	load_image(t_data *data, int *texture, char *path, t_img *img);

//key_func
void	key_w(t_data *data);
void	key_a(t_data *data);
void	key_s(t_data *data);
void	key_d(t_data *data);
int		key_exit(t_data *data);

#endif
