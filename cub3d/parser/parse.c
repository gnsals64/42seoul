/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:12:48 by junhyupa          #+#    #+#             */
/*   Updated: 2023/05/26 13:13:02 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	parser(char *av, t_cub *cub, t_data *data)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		error_control(strerror(errno), "file open Error", 1);
	parse_option(fd, cub);
	parse_map(fd, cub);
	close(fd);
	map_checker(cub->map, cub, data);
	if (data->cub.player == 0)
		error_control("No player Error", NULL, 1);
}
