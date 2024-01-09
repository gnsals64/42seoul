/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:49 by junhyupa          #+#    #+#             */
/*   Updated: 2023/05/26 14:00:53 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "cub3d.h"

void	*safe_calloc(size_t n, size_t size);
void	print_err(char *msg, char *msg2);
void	error_control(char *msg, char *msg2, int n);

void	free_tex(t_data *data);
void	free_all(t_data *data);
void	free_box(char **box);

#endif