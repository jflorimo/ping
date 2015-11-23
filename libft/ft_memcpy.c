/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 16:41:44 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 16:42:11 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char	*ss1;

	ss1 = (char *)s1;
	while (n--)
		*ss1++ = *((unsigned char *)s2++);
	return (s1);
}
