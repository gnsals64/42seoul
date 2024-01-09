/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:09:43 by junhyupa          #+#    #+#             */
/*   Updated: 2023/05/26 12:18:04 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	*safe_calloc(size_t n, size_t size)
{
	void	*rtn;

	rtn = ft_calloc(n, size);
	if (rtn)
		return (rtn);
	error_control(strerror(errno), "safe_calloc failed Error", 1);
	exit (1);
}

void	print_err(char *msg, char *msg2)
{
	ft_putstr_fd("cub3D: ", 2);
	ft_putstr_fd(msg, 2);
	if (msg2 && *msg2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg2, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	error_control(char *msg, char *msg2, int n)
{
	print_err(msg, msg2);
	exit (n);
}
