/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:43:13 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/10 12:04:43 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// int	ft_strncmp(const char *st1, const char *st2, size_t x)
// {
// 	size_t	n;

// 	n = 0;
// 	if (x == 0)
// 		return (0);
// 	while (n < x - 1 && st1[n] != '\0' && st2[n] != '\0' && st1[n] == st2[n])
// 	{
// 		n++;
// 	}
// 	return ((unsigned char)st1[n] - (unsigned char)st2[n]);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (start > i)
		len = 0;
	if (len > i - start)
		len = i - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (substr);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[x] != '\0')
	{
		str[x] = s1[x];
		x++;
	}
	while (s2[y] != '\0')
	{
		str[y + x] = s2[y];
		y++;
	}
	str[x + y] = '\0';
	return (str);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		x;

	x = 0;
	if (!s || fd < 0)
		return ;
	while (s[x] != '\0')
	{
		ft_putchar_fd(s[x], fd);
		x++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

