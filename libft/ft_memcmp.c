/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 16:41:07 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 16:41:30 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n && *((unsigned char *)s1) == *((unsigned char *)s2))
		return (ft_memcmp(s1 + 1, s2 + 1, n - 1));
	if (n)
		return (*((unsigned char *)s1) - *((unsigned char *)s2));
	return (0);
}
