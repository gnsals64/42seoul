/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhyupa <junhyupa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:38:17 by junhyupa          #+#    #+#             */
/*   Updated: 2022/08/09 14:38:17 by junhyupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cut_str(char **storage, size_t index)
{
	size_t	len;
	char	*output;
	char	*tmp;

	len = ft_strlen(*storage);
	if (len == 0)
	{
		free (*storage);
		*storage = NULL;
		return (NULL);
	}
	output = ft_strndup(*storage, 0, index);
	tmp = ft_strndup(*storage, index + 1, len - 1);
	free(*storage);
	*storage = tmp;
	return (output);
}

char	*ft_linejoin(char *storage, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(storage) + ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == 0)
		return (0);
	while (storage && storage[j])
		tmp[i++] = storage[j++];
	while (*s2)
		tmp[i++] = *s2++;
	tmp[i] = '\0';
	if (storage)
		free (storage);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		buf[BUFFER_SIZE + 1];
	size_t		index;
	ssize_t		read_num;
	size_t		cnt;

	cnt = 0;
	while (fd >= 0)
	{
		cnt++;
		read_num = read(fd, buf, BUFFER_SIZE);
		if ((!storage && !read_num) || read_num < 0)
			break ;
		buf[read_num] = '\0';
		storage = ft_linejoin(storage, buf);
		if (storage == 0)
			return (0);
		index = find_next(storage);
		if (index < BUFFER_SIZE * cnt)
			return (cut_str(&storage, index));
	}
	if (storage)
		free (storage);
	return (NULL);
}
