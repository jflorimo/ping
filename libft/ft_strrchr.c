/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 17:43:17 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 17:43:38 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*cc;

	cc = NULL;
	while (*s)
	{
		if (*s == (char)c)
			cc = (char *)s;
		s++;
	}
	if (*s == (char)c)
		cc = (char *)s;
	return (cc);
}
