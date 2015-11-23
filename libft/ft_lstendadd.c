/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstendadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 16:15:19 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 16:16:52 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstendadd(t_list **begin_list, t_list *new)
{
	t_list	*tmp_list;

	tmp_list = *begin_list;
	if (tmp_list == NULL)
		tmp_list = new;
	else
	{
		while (tmp_list->next != NULL)
			tmp_list = tmp_list->next;
		tmp_list->next = new;
	}
}
