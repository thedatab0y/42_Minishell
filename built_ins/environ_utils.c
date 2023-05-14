/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:34:46 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/10 11:34:57 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*env_lstnew(char **envp)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = ft_strdup(envp[0]);
	if (ft_strncmp(new->key, "SHLVL", 6) == 0)
		new->val = ft_itoa(ft_atoi(envp[1]) + 1);
	else
		new->val = ft_strdup(envp[1]);
	new->export = 1;
	new->next = NULL;
	return (new);
}

t_env	*env_lstlast(t_env *envs)
{
	if (envs == NULL)
		return (NULL);
	while (envs->next != NULL)
		envs = envs->next;
	return (envs);
}

void	env_lstadd_back(t_env **environ, t_env *new)
{
	t_env	*cur;

	if (environ == NULL || new == NULL)
		return ;
	if (*environ == NULL)
	{
		*environ = new;
		return ;
	}
	cur = env_lstlast(*environ);
	cur->next = new;
	new->next = NULL;
}

void	env_lstclear(t_env *environ)
{
	t_env	*cur;
	t_env	*tmp;

	if (environ == NULL)
		return ;
	cur = environ;
	while (cur != NULL)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
	environ = NULL;
}

int	env_lstlen(t_env *environ)
{
	t_env	*cur;
	int		len;

	if (environ == NULL)
		return (0);
	len = 0;
	cur = environ;
	while (cur != NULL)
	{
		cur = cur->next;
		len++;
	}
	return (len);
}