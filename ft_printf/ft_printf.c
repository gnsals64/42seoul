/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:46:35 by hunpark           #+#    #+#             */
/*   Updated: 2022/10/06 12:24:15 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_printf.h"

int	ft_word_cnt(va_list *ap, char *input)
{
	t_option	*op;
	int			i;
	int			word_cnt;

	i = 0;
	word_cnt = 0;
	op = (t_option *)malloc(sizeof(t_option));
	if (!op)
		return (-1);
	while (input[i])
	{
		if (input[i] == '%')
		{
			i++;
			i = ft_parsing(input, op, i);
			word_cnt = ft_print_it(ap, op, word_cnt);
		}
		if (i == -1 || word_cnt == -1)
			return (-1);
		if (input[i] != '\0' && input[i] != '%')
			ft_else_write(input, &word_cnt, &i);
	}
	free(op);
	return (word_cnt);
}

int	ft_printf(const char *input, ...)
{
	va_list		ap;
	int			word_cnt;
	char		*save;

	save = ft_strdup(input);
	if (!save)
		return (-1);
	word_cnt = 0;
	va_start(ap, input);
	word_cnt = ft_word_cnt(&ap, save);
	if (word_cnt == -1)
		return (-1);
	va_end(ap);
	free(save);
	return (word_cnt);
}
