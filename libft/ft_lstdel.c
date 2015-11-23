/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 16:12:48 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 16:13:52 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;
	t_list	*tmp;

	node = *alst;
	if (alst && *alst && (*del))
	{
		while (node)
		{
			tmp = node;
			node = node->next;
			(*del)(tmp->content, tmp->content_size);
			free(tmp);
		}
		*alst = NULL;
	}
}
