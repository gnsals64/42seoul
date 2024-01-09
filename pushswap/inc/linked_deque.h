/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Linked_deque.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:42:21 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/16 15:51:03 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_DEQUE_H
# define LINKED_DEQUE_H

typedef struct s_node
{
	struct s_node	*next;
	int				data;
	struct s_node	*prev;
}	t_node;

typedef struct s_deque
{
	int		cnt;
	t_node	*head;
	t_node	*tail;
}	t_deque;

typedef struct s_data
{
	int		*arr;
	bool	sort;
	t_deque	*deque_a;
	t_deque	*deque_b;
}	t_data;

t_deque	*init_info(void);
void	push_front(t_deque *deque, int data);
void	push_back(t_deque *deque, int data);
void	pop_front(t_deque *deque);
void	pop_back(t_deque *deque);
void	sa(t_data *data);
void	sb(t_data *data);
void	ss(t_data *data);
void	pa(t_data *data);
void	pb(t_data *data);
void	ra(t_data *data);
void	rb(t_data *data);
void	rr(t_data *data);
void	rra(t_data *data);
void	rrb(t_data *data);
void	rrr(t_data *data);

#endif
