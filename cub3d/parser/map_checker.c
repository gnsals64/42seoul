/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:05:28 by junhyupa          #+#    #+#             */
/*   Updated: 2023/05/26 13:53:26 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_elements(char c, t_data *data)
{
	if (!c || c == ' ' || c == '\n')
		return (1);
	else if (c == '1')
		return (2);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (data)
			data->cub.player++;
		return (3);
	}
	else if (c == '0')
		return (4);
	return (0);
}

static int	is_wall(char **map, t_cub *cub, int x, int y)
{
	if (x < 0 || y < 0 || x >= cub->map_width || y >= cub->map_height)
		return (1);
	if (is_elements(map[y][x], NULL) <= 1)
		return (1);
	return (0);
}

static int	check_caldinal(char **map, t_cub *cub, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			if (is_wall(map, cub, x + i, y + j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	check_user_direction(int x, int y, t_data *data)
{
	if (data->cub.player > 1)
		error_control("Put only one player Error", NULL, 1);
	data->player.pos_x = x + 0.5;
	data->player.pos_y = y + 0.5;
	if (data->cub.map[y][x] == 'N')
	{
		data->player.plane_x = 0.66;
		data->player.dir_y = -1;
	}
	if (data->cub.map[y][x] == 'W')
	{
		data->player.plane_y = -0.66;
		data->player.dir_x = -1;
	}
	if (data->cub.map[y][x] == 'S')
	{
		data->player.plane_x = -0.66;
		data->player.dir_y = 1;
	}
	if (data->cub.map[y][x] == 'E')
	{
		data->player.plane_y = 0.66;
		data->player.dir_x = 1;
	}
}

void	map_checker(char **map, t_cub *cub, t_data *data)
{
	int	x;
	int	y;
	int	elements;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y][x] != '\n')
		{
			elements = is_elements(map[y][x], data);
			if (elements == 0)
				error_control("Invailid map elements Error", NULL, 1);
			if ((y == 0 || y == cub->map_height || x == 0) && \
				(map[y][x] != ' ' && map[y][x] != '1'))
				error_control("need surrounded by wall map Error", NULL, 1);
			if (elements >= 3 && check_caldinal(map, cub, x, y))
				error_control("need surrounded by wall map Error", NULL, 1);
			if (elements == 3)
				check_user_direction(x, y, data);
			x++;
		}
		y++;
	}
}
