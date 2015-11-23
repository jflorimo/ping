/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 17:41:32 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 17:41:47 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	if (!n || (!*s1 && !*s2))
		return (1);
	else if (*s1 == *s2)
		return (ft_strnequ(s1 + 1, s2 + 1, n - 1));
	return (0);
}
