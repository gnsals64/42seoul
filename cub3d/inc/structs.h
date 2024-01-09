/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:56:12 by junhyupa          #+#    #+#             */
/*   Updated: 2023/05/26 16:28:42 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum e_direct{
	NO,
	SO,
	WE,
	EA,
};

typedef struct s_cub
{
	char		**map;
	char		*texture[4];
	int			f_color;
	int			c_color;
	int			map_width;
	int			map_height;
	int			player;
}	t_cub;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line_size;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	int		player_size;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	double	wall_x;
	int		texnum;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

}	t_ray;

typedef struct s_tex
{
	int		*tex[4];
	void	*tex_img[4];
	int		**buf;
	int		re_buf;
}	t_tex;

typedef struct s_data
{
	t_player	player;
	t_img		img;
	t_mlx		mlx;
	t_cub		cub;
	t_tex		tex;
	t_ray		ray;
}	t_data;

#endif
