/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 16:31:11 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 16:32:20 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstrev(t_list **begin)
{
	t_list	*head;
	t_list	*tmp;
	t_list	*tmp1;

	head = *begin;
	tmp = NULL;
	while (head != NULL)
	{
		tmp1 = tmp;
		tmp = head;
		head = head->next;
		tmp->next = tmp1;
	}
	*begin = tmp;
}
