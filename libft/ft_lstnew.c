/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 16:28:46 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 16:29:34 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	if ((node = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content)
	{
		if ((node->content = (void *)malloc(content_size)) == NULL)
			return (NULL);
		node->content = ft_memmove(node->content, content, content_size);
	}
	else
		node->content = NULL;
	node->content_size = !content ? 0 : content_size;
	node->next = NULL;
	return (node);
}
