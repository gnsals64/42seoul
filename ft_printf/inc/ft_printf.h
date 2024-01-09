/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 03:50:34 by hunpark           #+#    #+#             */
/*   Updated: 2022/09/30 04:38:57 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct flag_list
{
	bool	minus;
	bool	plus;
	bool	blank;
	bool	cross;
	bool	zero;
}	t_flag;

typedef struct option
{
	t_flag	flag;
	bool	dot;
	int		w;
	int		p;
	char	t;
}	t_option;

bool	ft_isflag(char a);
bool	ft_istype(char a);
void	ft_flag_on(t_option *op, char a);
int		ft_width_precision_check(t_option *op, char *str, int i, int flag);
void	ft_sep(t_option *op, char *str);
int		ft_parsing(char *input, t_option *op, int i);
void	ft_putstr(char *str);
int		ft_print_it(va_list *ap, t_option *op, int word_cnt);
int		ft_word_cnt(va_list *ap, char *input);
int		ft_printf(const char *input, ...);
int		ft_print_c(va_list *ap, t_option *op);
int		ft_print_s(va_list *ap, t_option *op);
int		ft_print_s_minus(t_option *op, char *str);
int		ft_print_s_non(t_option *op, char *str);
char	*ft_fill_space(int w);
int		ft_print_c_minus(t_option *op, char c);
void	ft_else_write(char *str, int *word_cnt, int *i);
int		ft_print_p(va_list *ap, t_option *op);
int		find_digit_hex(unsigned long long num);
int		find_digit(long long num, int n);
int		ft_print_d(va_list *ap, t_option *op);
char	*ft_itoa_d(int n, t_option *op);
char	*ft_uitoa(unsigned int n);
char	*ft_uitoa_u(unsigned int n, t_option *op);
int		ft_print_u_w(char *str, t_option *op);
int		ft_print_u(va_list *ap, t_option *op);
char	*ft_uitoa_u_zero(unsigned int n, t_option *op);
char	*ft_uitoa_u_p_1(unsigned int n);
char	*ft_uitoa_u_p_2(unsigned int n, t_option *op);
int		ft_print_x(va_list *ap, t_option *op);
char	*ft_uitox_u(unsigned int n, t_option *op);
char	*ft_uitox_u_l(unsigned int n, t_option *op);
char	ft_find_hex(char *base, int num);
int		ft_print_x_l(va_list *ap, t_option *op);
int		ft_print_x_w_zero(char *str, t_option *op, int flag, unsigned int num);
int		ft_print_per(t_option *op);
int		ft_print_x_w(char *str, t_option *op, int flag, unsigned int num);

#endif
