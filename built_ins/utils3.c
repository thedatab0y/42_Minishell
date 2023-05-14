/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:43:19 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/10 11:36:13 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	ft_memcpy(new_ptr, ptr, size);
	return (new_ptr);
}

void	*ft_memcpy(void *to, const void *from, size_t n)
{
	unsigned char	*pto;
	unsigned char	*pfrom;
	size_t			x;

	if (to == NULL && from == NULL)
		return (NULL);
	pto = (unsigned char *)to;
	pfrom = (unsigned char *)from;
	x = 0;
	while (x < n)
	{
		pto[x] = pfrom[x];
		x++;
	}
	return (pto);
}

int	ft_atoi(const char *str)
{
	long int	result;
	int			x;
	int			sign;
	long int	old_num;

	result = 0;
	sign = 1;
	x = 0;
	while (str[x] == 32 || (str[x] >= 9 && str[x] <= 13))
		x++;
	if (str[x] == '-')
		sign *= -1;
	if (str[x] == '+' || str[x] == '-')
		x++;
	while (str[x] >= '0' && str[x] <= '9')
	{
		old_num = result;
		result = result * 10 + str[x] - '0';
		if ((old_num < 0 && result > 0) || (old_num > 0 && result < 0))
			return ((sign == 1) * -1);
		x++;
	}
	return (result * sign);
}

