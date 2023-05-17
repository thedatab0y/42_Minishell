/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:10:41 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/17 23:02:38 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	x;

	x = 0;
	while (s1[x] || s2[x])
	{
		if (s1[x] != s2[x])
		{
			return ((unsigned char)s1[x] - (unsigned char)s2[x]);
		}
	x++;
	}
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
