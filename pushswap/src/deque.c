/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunpark <hunpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:06:30 by hunpark           #+#    #+#             */
/*   Updated: 2023/02/17 22:10:22 by hunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

t_deque	*init_info(void)
{
	t_deque	*lst;

	lst = (t_deque *)malloc(sizeof(t_deque));
	if (!lst)
		return (NULL);
	lst->cnt = 0;
	lst->head = NULL;
	lst->tail = NULL;
	return (lst);
}

void	push_front(t_deque *deque, int data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return ;
	if (deque->head == NULL)
	{
		deque->head = node;
		deque->tail = node;
		node->next = NULL;
		node->prev = NULL;
		node->data = data;
		deque->cnt++;
		return ;
	}
	deque->head->prev = node;
	node->next = deque->head;
	deque->head = node;
	node->prev = NULL;
	node->data = data;
	deque->cnt++;
}

void	push_back(t_deque *deque, int data)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return ;
	if (deque->tail == NULL)
	{
		deque->head = node;
		deque->tail = node;
		node->next = NULL;
		node->prev = NULL;
		node->data = data;
		deque->cnt++;
		return ;
	}
	deque->tail->next = node;
	node->prev = deque->tail;
	deque->tail = node;
	node->next = NULL;
	node->data = data;
	deque->cnt++;
}

void	pop_front(t_deque *deque)
{
	t_node	*tmp;

	if (deque->head == NULL)
	{
		write(1, "error\n", 6);
		return ;
	}
	tmp = deque->head;
	if (deque->cnt != 1)
		deque->head->next->prev = NULL;
	deque->head = deque->head->next;
	deque->cnt--;
	free(tmp);
}

void	pop_back(t_deque *deque)
{
	t_node	*tmp;

	if (deque->head == NULL)
	{
		write(1, "error\n", 6);
		return ;
	}
	if (deque->cnt != 1)
		deque->tail->prev->next = NULL;
	tmp = deque->tail;
	deque->tail = deque->tail->prev;
	deque->cnt--;
	free(tmp);
}
