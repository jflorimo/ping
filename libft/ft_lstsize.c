/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 16:32:57 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 16:33:43 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstsize(t_list *begin)
{
	t_list	*node;
	int		i;

	i = 0;
	node = begin;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}
