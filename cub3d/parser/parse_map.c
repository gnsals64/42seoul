/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:41:03 by junhyupa          #+#    #+#             */
/*   Updated: 2023/05/26 13:15:44 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	get_width_height(t_cub *cub, char **map)
{
	size_t	map_width;
	size_t	map_height;

	map_width = 0;
	map_height = 0;
	while (map[map_height])
	{
		if (ft_strlen(map[map_height]) > map_width)
			map_width = ft_strlen(map[map_height]);
		map_height++;
	}
	cub->map_width = map_width;
	cub->map_height = map_height;
}

static char	**add_map(char **map, char *s)
{
	int		i;
	char	**rtn;

	i = 0;
	while (map && map[i])
		i++;
	rtn = safe_calloc(sizeof(char *), i + 2);
	rtn[i + 1] = NULL;
	rtn[i] = s;
	while (--i >= 0)
		rtn[i] = map[i];
	free(map);
	return (rtn);
}

static void	cpy_map(t_cub *cub, char **map)
{
	int	i;

	i = 0;
	cub->map = safe_calloc(sizeof(char *), cub->map_height + 1);
	while (i < cub->map_height && map[i])
	{
		cub->map[i] = safe_calloc(sizeof(char), cub->map_width + 1);
		ft_strlcpy(cub->map[i], map[i], cub->map_width + 1);
		i++;
	}
}

void	parse_map(int fd, t_cub *cub)
{
	char	*tmp;
	char	**map;
	int		i;

	map = NULL;
	tmp = get_next_line(fd);
	while (tmp && !ft_strncmp(tmp, "\n", 2))
	{
		free (tmp);
		tmp = get_next_line(fd);
	}
	while (tmp && *tmp)
	{
		map = add_map(map, tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	if (!map)
		error_control("Invalid map error", NULL, 1);
	get_width_height(cub, map);
	cpy_map(cub, map);
	free_box(map);
}
