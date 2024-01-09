/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:54:47 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/23 14:59:21 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "push_swap.h"
# include "../gnl/get_next_line.h"

void	run_swap_push(t_data *data, char *buf, bool *flag);
void	run_rotate(t_data *data, char *buf, bool *flag);
int		first_sort_check(t_data *data);
void	sort_check(t_data *data);
void	checker(t_data *data);

#endif
