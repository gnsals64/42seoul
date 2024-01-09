/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:00:44 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/16 15:19:08 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	ft_find_word(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != 0 && i != 0)
			cnt++;
		i++;
	}
	if (cnt == 0)
		return (0);
	return (cnt);
}

int	ft_save_join(char **save, char **tmp, int *i)
{
	int	j;

	j = 0;
	while (tmp[j] != NULL)
	{
		save[*i] = ft_strdup(tmp[j]);
		if (!save[*i])
		{
			ft_free_save(save, *i);
			return (-1);
		}
		j++;
		(*i)++;
	}
	return (0);
}

int	ft_save_insert(char **save, char *av, int *i)
{
	char	**tmp;
	int		j;
	int		check;

	j = -1;
	check = 0;
	while (av[++j])
	{
		if (av[j] == ' ')
			check++;
	}
	tmp = ft_split(av, ' ');
	if (!tmp || check == (int)ft_strlen(av))
	{
		ft_double_free(tmp);
		return (-1);
	}
	if (ft_save_join(save, tmp, i) == -1)
		return (-1);
	j = -1;
	ft_double_free(tmp);
	return (0);
}

char	**ft_sep(int ac, char **av)
{
	char	**save;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ac;
	while (++i < ac)
		len += ft_find_word(av[i]);
	save = (char **)malloc(sizeof(char *) * len);
	if (!save)
		return (NULL);
	save[len - 1] = NULL;
	i = 0;
	while (++i < ac)
	{
		if (ft_save_insert(save, av[i], &j) == -1)
		{
			ft_double_free(save);
			return (NULL);
		}
	}
	return (save);
}

int	*ft_parsing(int ac, char **av, int *arr_len, int *error)
{
	int		*save;
	char	**tmp;
	int		i;
	int		len;

	i = -1;
	len = 0;
	tmp = ft_sep(ac, av);
	if (!tmp)
		return (NULL);
	while (tmp[len] != NULL)
		len++;
	*arr_len = len;
	save = (int *)malloc(sizeof(int) * len);
	if (!save)
		return (NULL);
	while (tmp[++i] != NULL)
		save[i] = ft_atoi_errorhandle(tmp[i], error);
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
	return (save);
}
