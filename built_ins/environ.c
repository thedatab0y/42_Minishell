/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:32:41 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/10 11:33:05 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_env(t_env *environ, char *key)
{
	t_env	*cur;

	cur = environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key) + 1) == 0)
			return (cur->val);
		cur = cur->next;
	}
	return (NULL);
}

char	**get_environ(t_env *environ)
{
	t_env	*cur;
	char	**envp;
	char	*tmp;
	int		i;

	envp = (char **)malloc(sizeof(char *) * env_lstlen(environ) + 1);
	if (envp == NULL)
		return (NULL);
	i = 0;
	cur = environ;
	while (cur != NULL)
	{
		if (cur->val == NULL)
			envp[i] = ft_strjoin(cur->key, "=");
		else
		{
			tmp = ft_strjoin("=", cur->val);
			envp[i] = ft_strjoin(cur->key, tmp);
			free(tmp);
		}
		i++;
		cur = cur->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	delete_environ(t_env *environ, char *key)
{
	t_env	*tmp;
	t_env	*cur;

	if (environ->next == NULL \
		&& (!ft_strncmp(environ->key, key, ft_strlen(environ->key) + 1)))
	{
		free(environ->key);
		free(environ->val);
		free(environ);
	}
	cur = environ;
	while (cur->next != NULL)
	{
		if (!ft_strncmp(cur->next->key, key, ft_strlen(cur->next->key) + 1))
		{
			tmp = cur->next;
			cur->next = tmp->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
			return ;
		}
		cur = cur->next;
	}
}

void	add_environ(t_env *environ, char *key, char *val, int export)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return ;
	new->key = key;
	new->val = val;
	new->export = export;
	new->next = NULL;
	env_lstadd_back(&environ, new);
}

t_env	*set_environ(char **envp)
{
	t_env	*environ;
	char	**envs;
	int		i;
	int		j;

	environ = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		envs = ft_split(envp[i], '=');
		if (envs == NULL)
			return (NULL);
		env_lstadd_back(&environ, env_lstnew(envs));
		j = 0;
		while (envs[j])
		{
			if (envs[j] != NULL)
				free(envs[j]);
			j++;
		}
		free(envs);
		i++;
	}
	return (environ);
}
