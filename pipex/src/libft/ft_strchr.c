/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:05:18 by hunpark           #+#    #+#             */
/*   Updated: 2023/01/25 21:00:00 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (c > 256)
		c %= 256;
	while (*str != c)
	{
		if (*str == 0)
			return ((char *)(str - i));
		str++;
		i++;
	}
	return ((char *)str);
}
