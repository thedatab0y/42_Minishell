/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:03:40 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/10 10:07:31 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int	check_export_type(char *cmd)
{
	int	i;

	if (cmd[0] == '\0' || cmd[0] == '+' || cmd[0] == '=')
		return (0);
	i = 0;
	while (cmd[i] != '\0')
	{
		if (i == 0 && ('0' <= cmd[i] && cmd[i] <= '9'))
			return (0);
		if (is_meta_builtin(cmd[i]))
		{
			if (cmd[i] == '=')
				return ('=');
			if (cmd[i] == '+' && cmd[i + 1] == '=')
				return ('+');
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_key(char *command)
{
	int		i;
	char	*key;

	i = 0;
	while (command[i] != '\0')
	{
		if (is_meta_builtin(command[i]))
			break ;
		i++;
	}
	key = (char *)malloc(sizeof(char *) * i + 1);
	if (key == NULL)
		return (NULL);
	i = 0;
	while (command[i] != '\0')
	{
		if (is_meta_builtin(command[i]))
			break ;
		key[i] = command[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	get_value_len(char *command)
{
	int	i;
	int	val_count;

	i = 0;
	val_count = 0;
	while (command[i] != '\0')
	{
		if (val_count)
			val_count++;
		if (command[i] == '=' && !val_count)
			val_count = 1;
		i++;
	}
	return (val_count - 1);
}

char	*get_value(char *command)
{
	int		i;
	int		val_count;
	char	*value;

	val_count = get_value_len(command);
	if (val_count < 1)
		return (NULL);
	value = (char *)malloc(sizeof(char *) * val_count + 1);
	if (value == NULL)
		return (NULL);
	i = 0;
	val_count = 0;
	while (command[i] != '\0')
	{
		if (val_count)
			value[val_count++ - 1] = command[i];
		if (command[i++] == '=' && !val_count)
			val_count = 1;
	}
	value[val_count - 1] = '\0';
	return (value);
}

void	print_export_value(char *value)
{
	int	i;

	if (value == NULL)
		return ;
	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '\"')
		{
			ft_putchar_fd('\\', 1);
			ft_putchar_fd('\"', 1);
		}
		else
			ft_putchar_fd(value[i], 1);
		i++;
	}
}
