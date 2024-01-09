/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:57:27 by junhyupa          #+#    #+#             */
/*   Updated: 2023/05/26 17:47:46 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	parse_color(char *s)
{
	int	i;
	int	tmp;
	int	rtn;

	i = 0;
	rtn = 0;
	while (s && *s && ++i)
	{
		tmp = -1;
		while (ft_isdigit(*s) && tmp <= 255)
		{
			if (tmp < 0)
				tmp = 0;
			tmp *= 10;
			tmp += *s++ - '0';
		}
		if (tmp < 0 || tmp > 255 || (*s && (*s != ',' || i == 3)))
			error_control("invalid color elements Error", NULL, 1);
		rtn = rtn << 8;
		rtn += tmp;
		s++;
	}
	if (i != 3)
		error_control("invalid color elements Error", NULL, 1);
	return (rtn);
}

static char	*skip_space(char *s)
{
	while (s && *s && *s == ' ')
		s++;
	return (s);
}

static int	get_option_value(t_cub *cub, char *tmp)
{
	if (ft_strlen(tmp) >= 1 && tmp[ft_strlen(tmp) - 1] == '\n')
		tmp[ft_strlen(tmp) - 1] = 0;
	if (!cub->texture[NO] && !ft_strncmp(tmp, "NO ", 3))
		cub->texture[NO] = ft_strdup(skip_space(&tmp[3]));
	else if (!cub->texture[WE] && !ft_strncmp(tmp, "WE ", 3))
		cub->texture[WE] = ft_strdup(skip_space(&tmp[3]));
	else if (!cub->texture[SO] && !ft_strncmp(tmp, "SO ", 3))
		cub->texture[SO] = ft_strdup(skip_space(&tmp[3]));
	else if (!cub->texture[EA] && !ft_strncmp(tmp, "EA ", 3))
		cub->texture[EA] = ft_strdup(skip_space(&tmp[3]));
	else if (!cub->f_color && !ft_strncmp(tmp, "F ", 2))
		cub->f_color = parse_color(skip_space(&tmp[2]));
	else if (!cub->c_color && !ft_strncmp(tmp, "C ", 2))
		cub->c_color = parse_color(skip_space(&tmp[2]));
	else if (ft_strncmp(tmp, "\0", 1))
		error_control("Invalid option value error", NULL, 1);
	else
		return (0);
	return (1);
}

void	parse_option(int fd, t_cub *cub)
{
	char	*tmp;
	int		cnt;

	cnt = 0;
	tmp = get_next_line(fd);
	while (cnt < 6 && tmp && *tmp)
	{
		if (get_option_value(cub, tmp))
			++cnt;
		free(tmp);
		if (cnt < 6)
			tmp = get_next_line(fd);
	}
	if (cnt < 6)
		error_control("Need all options Error", NULL, 1);
}
