/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 17:18:30 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 17:18:50 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *s1, const char *s2)
{
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	while (*s1)
		s1++;
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
	return (s1 - len);
}
