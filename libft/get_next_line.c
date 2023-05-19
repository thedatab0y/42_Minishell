/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:57:36 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:21:36 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	newline_check(char *stock, int read_size)
{
	int	i;

	i = 0;
	if (read_size == 0 && stock[0] == '\0')
		return (2);
	if (read_size == 0 || stock == NULL)
		return (0);
	while (stock[i] != '\0')
	{
		if (stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*buf_join(char *stock, char *buf)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (stock != NULL && stock[i] != '\0')
		i++;
	while (buf[j] != '\0')
		j++;
	new = malloc(sizeof(char) * (i + j + 1));
	if (!new)
		return (ft_memdel(stock));
	i = 0;
	j = 0;
	while (stock != NULL && stock[i] != '\0')
		new[i++] = stock[j++];
	j = 0;
	while (buf[j] != '\0')
		new[i++] = buf[j++];
	new[i] = '\0';
	if (stock != NULL)
		ft_memdel(stock);
	return (new);
}

char	*stock_trim(char *stock)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	while (stock[i++] != '\0')
		j++;
	trimmed = malloc(sizeof(char) * j + 1);
	if (!trimmed)
		return (ft_memdel(stock));
	i = 0;
	j = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	if (stock[i] == '\0')
		i--;
	i++;
	while (stock[i] != '\0')
		trimmed[j++] = stock[i++];
	trimmed[j] = '\0';
	ft_memdel(stock);
	return (trimmed);
}

char	*get_line(char *stock)
{
	int		i;
	char	*line;

	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (ft_memdel(stock));
	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	get_next_line(int fd, char **line)
{
	static char	*stock = NULL;
	int			read_len;

	if (line == NULL || fd < 0 || BUFFER_SIZE < 1 || (read(fd, NULL, 0)) < 0)
		return (-1);
	read_len = read_from_file(fd, &stock);
	if (read_len == -1)
		return (-1);
	*line = stock;
	if (newline_check(stock, read_len) == 2 && *line)
		return (-2);
	*line = get_line(stock);
	if (*line == NULL)
		return (-1);
	stock = stock_trim(stock);
	if (stock)
		return (-1);
	ft_memdel(stock);
	if (read_len != 0)
		return (1);
	else
		return (0);
}
