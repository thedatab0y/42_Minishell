/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:55:02 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/10 12:05:59 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	export_append(char *cmd, t_env *environ)
{
	char	*key;
	char	*value;
	char	*tmp;
	t_env	*cur;

	key = get_key(cmd);
	value = get_value(cmd);
	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key) + 1) == 0)
		{
			if (cur->val != NULL)
				tmp = ft_strjoin(cur->val, value);
			else
				tmp = ft_strdup(value);
			free(cur->val);
			cur->val = tmp;
			cur->export = 1;
			free_strings(key, value);
			return ;
		}
		cur = cur->next;
	}
	add_environ(environ, key, value, 1);
}

void	export_replace(char *cmd, t_env *environ)
{
	char	*key;
	char	*value;
	t_env	*cur;

	key = get_key(cmd);
	value = get_value(cmd);
	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key) + 1) == 0)
		{
			free(cur->val);
			cur->val = value;
			cur->export = 1;
			free(key);
			return ;
		}
		cur = cur->next;
	}
	add_environ(environ, key, value, 1);
}

void	export_add(char *cmd, t_env *environ)
{
	t_env	*cur;
	int		found;
	char	*key;

	found = 0;
	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, cmd, ft_strlen(cur->key) + 1) == 0)
			found = 1;
		cur = cur->next;
	}
	key = ft_strdup(cmd);
	if (!found)
		add_environ(environ, key, NULL, 0);
	else
		free(key);
}

void	show_export(t_env *environ)
{
	t_env	*cur;

	cur = environ;
	while (cur != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		if (cur->export)
		{
			ft_putstr_fd(cur->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			print_export_value(cur->val);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd(cur->key, 1);
			ft_putstr_fd("\n", 1);
		}
		cur = cur->next;
	}
}

int	ft_export(t_cmd *node, t_env *environ)
{
	int	i;
	int	type;
	int	status;

	i = 1;
	if (node->args[i] == NULL)
		show_export(environ);
	status = EXIT_SUCCESS;
	while (node->args[i] != NULL)
	{
		type = check_export_type(node->args[i]);
		if (!type)
		{
			export_identifier_error(node->args[i]);
			status = EXIT_FAILURE;
		}
		else if (type == '=')
			export_replace(node->args[i], environ);
		else if (type == '+')
			export_append(node->args[i], environ);
		else
			export_add(node->args[i], environ);
		i++;
	}
	return (status);
}

#include <stdlib.h>
#include <stdio.h>

int main() {
    char* env_var = "MY_VAR=hello"; // set the environment variable
    char* cmd = "echo $MY_VAR"; // print the value of the environment variable
    setenv("MY_VAR", "hello", 1); // set the environment variable
    putenv(env_var); // export the environment variable
    system(cmd); // print the value of the environment variable
    return 0;
}