/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 17:51:23 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 17:51:58 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_is_whitespace(char const c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	int			len;

	if (!s)
		return (NULL);
	while (*s && ft_is_whitespace(*s))
		s++;
	len = ft_strlen(s) - 1;
	while (len > 0 && s[len] && ft_is_whitespace(s[len]))
		len--;
	return (ft_strsub(s, 0, len + 1));
}
