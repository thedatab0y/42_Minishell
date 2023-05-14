/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:43:08 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/10 12:03:45 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	x;

	x = 0;
	new = (char *)malloc(sizeof(*new) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	while (s[x])
	{
		new[x] = s[x];
		x++;
	}
	new[x] = '\0';
	return (new);
}


int	ft_strncmp(const char *st1, const char *st2, size_t x)
{
	size_t	n;

	n = 0;
	if (x == 0)
		return (0);
	while (n < x - 1 && st1[n] != '\0' && st2[n] != '\0' && st1[n] == st2[n])
	{
		n++;
	}
	return ((unsigned char)st1[n] - (unsigned char)st2[n]);
}

size_t	ft_strlcat(char *to, const char *from, size_t tosize)
{
	size_t	x;
	size_t	pto;
	size_t	pfrom;
	size_t	y;

	pto = ft_strlen(to);
	pfrom = ft_strlen(from);
	x = pto;
	if (to == from)
		return (0);
	if (tosize != 0 && x < (tosize - 1))
	{
		y = 0;
		while (x < (tosize - 1) && from[y] != '\0')
		{
			to[x] = from[y];
			x++;
			y++;
		}
		to[x] = '\0';
	}
	if (pto > tosize)
		return (tosize + pfrom);
	return (pto + pfrom);
}

int	ft_strequ(const char *s1, const char *s2)
{
	size_t i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int ft_strlen(const char *string)
{
	int x;

	x = 0;
	while (string[x])
		x++;
	return(x);
}