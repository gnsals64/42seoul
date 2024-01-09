/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:05:15 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/19 21:11:47 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!(s1))
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (ft_strdup_gnl(s1));
	i = 0;
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	while (i < len1)
		str[i++] = *s1++;
	while (i < (len1 + len2))
		str[i++] = *s2++;
	str[i] = '\0';
	free(s1 - len1);
	return (str);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	a;

	a = 0;
	while (*s++)
		a++;
	return (a);
}

int	ft_strchr_gnl(const char *str, int c)
{
	char	a;
	int		i;

	a = c;
	i = 0;
	while (str[i])
	{
		if (str[i] == a)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup_gnl(const char *s)
{
	size_t	len;
	size_t	i;
	char	*tmp;

	i = 0;
	len = ft_strlen_gnl(s);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	while (i < len)
		tmp[i++] = *s++;
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	const size_t	s_len = ft_strlen_gnl(s);
	char			*str;
	int				i;
	size_t			substr_len;
	size_t			save_len;

	i = 0;
	save_len = len;
	if (!s)
		return (NULL);
	if (s_len < start)
		return (NULL);
	substr_len = 0;
	while (s[substr_len++] && substr_len < s_len && len--)
		;
	str = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (!str)
		return (NULL);
	while (s[start++] && save_len--)
		str[i++] = s[start - 1];
	str[i] = '\0';
	return (str);
}
