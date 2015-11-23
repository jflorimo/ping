/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 16:39:39 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 16:40:05 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	if (n)
	{
		if (*((unsigned char *)s) == (unsigned char)c)
			return ((void *)s);
		else
			return (ft_memchr(++s, c, --n));
	}
	return (NULL);
}
