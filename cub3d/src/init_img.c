/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:59:49 by hupa              #+#    #+#             */
/*   Updated: 2023/05/26 16:42:25 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_init_img(t_data *data)
{
	t_img	img;

	img.img = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.line_size,
			&img.endian);
	data->img = img;
}

void	ft_init_buf(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->tex.buf = safe_calloc(sizeof(int *), HEIGHT);
	while (i < HEIGHT)
		data->tex.buf[i++] = safe_calloc(sizeof(int), WIDTH);
	data->tex.re_buf = 0;
}

void	ft_init_tex(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
		data->tex.tex[i++] = safe_calloc(sizeof(int), TEX_H * TEX_W);
}

void	load_image(t_data *data, int *texture, char *path, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	img->img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, path, &img->img_width,
			&img->img_height);
	if (!img->img)
		error_control("Not found xpm file Error", NULL, 1);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_size,
			&img->endian);
	while (i < img->img_height)
	{
		j = 0;
		while (j < img->img_width)
		{
			texture[img->img_width * i + j] = img->addr[img->img_width * i + j];
			j++;
		}
		i++;
	}
	mlx_destroy_image(data->mlx.mlx_ptr, img->img);
}

void	load_texture(t_data *data)
{
	t_img	img;

	load_image(data, data->tex.tex[NO], data->cub.texture[NO], &img);
	load_image(data, data->tex.tex[SO], data->cub.texture[SO], &img);
	load_image(data, data->tex.tex[WE], data->cub.texture[WE], &img);
	load_image(data, data->tex.tex[EA], data->cub.texture[EA], &img);
}
