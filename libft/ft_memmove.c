/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 17:05:34 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 17:06:11 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	tmp[n];
	char	*s;

	i = 0;
	s = (char *)s1;
	while (i < n)
		tmp[i++] = *((char *)s2++);
	while (i--)
		s[i] = tmp[i];
	return (s1);
}
