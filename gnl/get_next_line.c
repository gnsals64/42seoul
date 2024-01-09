/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:58:21 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/19 21:10:21 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_split_save(char **save)
{
	char	*str1;
	char	*str2;
	int		i;
	int		i2;

	i = ft_strchr(*save, '\n');
	if (i != -1 && (ft_strlen(*save) - i) > 1)
	{
		i = i + 1;
		i2 = ft_strlen(*save) - i;
		str1 = ft_substr(*save, 0, i);
		str2 = ft_substr(*save, i, i2);
		free(*save);
		*save = ft_strdup(str2);
		free(str2);
		return (str1);
	}
	else
	{
		str1 = ft_strdup(*save);
		free(*save);
		*save = NULL;
		return (str1);
	}
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	len = read(fd, buf, BUFFER_SIZE);
	while (len > 0)
	{
		buf[len] = '\0';
		save = ft_strjoin(save, buf);
		if (ft_strchr(save, '\n') != -1)
			return (ft_split_save(&save));
		len = read(fd, buf, BUFFER_SIZE);
	}
	if (!save)
		return (NULL);
	return (ft_split_save(&save));
}

typdef struct s_list
{
	char *save;
	int fd;
	char * next;
}	t_list;

t_list->

node->save
