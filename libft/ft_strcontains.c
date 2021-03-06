/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 17:20:35 by jflorimo          #+#    #+#             */
/*   Updated: 2013/12/07 17:20:55 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcontains(char *s, char c)
{
	int	i;

	i = 0;
	if (!*s)
		return (-1);
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}
