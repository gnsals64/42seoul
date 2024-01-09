/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:34:46 by junhyupa          #+#    #+#             */
/*   Updated: 2023/05/26 13:13:34 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

void	parser(char *av, t_cub *cub, t_data *data);
void	parse_map(int fd, t_cub *cub);
void	map_checker(char **map, t_cub *cub, t_data *data);
void	parse_option(int fd, t_cub *cub);

#endif