/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:57:36 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/17 23:49:42 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	*ft_read_it(char **buffer, int fd)
{
	int		byte_count;
	char	*temp;
	char	*ptr;

	byte_count = 1;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (!(ft_strchr(*buffer, '\n')) && byte_count > 0)
	{
		byte_count = read(fd, temp, BUFFER_SIZE);
		if (byte_count)
		{
			temp[byte_count] = '\0';
			ptr = *buffer;
			*buffer = ft_strjoin(*buffer, (char *)temp);
			free(ptr);
		}
	}
	free(temp);
	temp = NULL;
	return (*buffer);
}

static int	ft_what_is_read(char **buffer, char **line)
{
	char	*p;
	char	*mem;

	p = NULL;
	if (ft_strchr(*buffer, '\n') == 0)
	{
		*line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (0);
	}
	else if (ft_strchr(*buffer, '\n') != 0)
	{
		mem = ft_strchr(*buffer, '\n');
		*line = malloc(sizeof(char) * (mem - *buffer + 1));
		if (!(*line))
			return (-1);
		*line = ft_strncpy(*line, *buffer, (mem - *buffer));
		p = *buffer;
		*buffer = ft_strdup(mem + 1);
		free(p);
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*buffer;

	buffer = NULL;
	if (line == NULL || fd < 0 || read(fd, buffer, 0) < 0 || BUFFER_SIZE < 0)
		return (-1);
	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer)
		return (-1);
	if (BUFFER_SIZE == 0)
	{
		*line = NULL;
		return (0);
	}
	buffer = ft_read_it(&buffer, fd);
	return (ft_what_is_read(&buffer, line));
}
