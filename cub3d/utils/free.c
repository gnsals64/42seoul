/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:23:58 by junhyupa          #+#    #+#             */
/*   Updated: 2023/05/26 14:06:42 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_tex(t_data *data)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
		free(data->tex.buf[i++]);
	free(data->tex.buf);
	i = 0;
	while (i < 4)
		free(data->tex.tex[i++]);
}

void	free_box(char **box)
{
	int	i;

	i = 0;
	while (box && box[i])
		free(box[i++]);
	if (box)
		free(box[i]);
	free(box);
}

void	free_all(t_data *data)
{
	free_box(data->cub.map);
	mlx_destroy_image(data->mlx.mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.mlx_win);
	free_tex(data);
}
