/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:21:45 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:22:11 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	read_from_file(int fd, char **stock)
{
	char	buf[BUFFER_SIZE + 1];
	int		read_len;

	read_len = 1;
	while (!(newline_check(*stock, read_len)))
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len == -1)
			return (-1);
		buf[read_len] = '\0';
		*stock = buf_join(*stock, buf);
		if (*stock == NULL)
			return (-1);
	}
	return (read_len);
}
