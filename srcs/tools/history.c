/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:41:59 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 20:08:52 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*history_init(void)
{
	t_history	*h;

	h = (t_history *)malloc(sizeof(t_history));
	h->head = NULL;
	h->size = 0;
	return (h);
}

void	history_add(t_history *h, const char *command)
{
	t_historyEntry	*entry;

	entry = (t_historyEntry *)malloc(sizeof(t_historyEntry));
	entry->command = strdup(command);
	entry->next = h->head;
	h->head = entry;
	h->size++;
}

char	*history_get(t_history *h, int index)
{
	int				i;
	t_historyEntry	*current;

	i = 0;
	current = h->head;
	if (index >= h->size)
		return (NULL);
	while (i < index)
	{
		current = current->next;
		i++;
	}
	return (current->command);
}

void	history_delete(t_history *h)
{
	t_historyEntry	*current;
	t_historyEntry	*next;

	current = h->head;
	while (current != NULL)
	{
		next = current->next;
		free(current->command);
		free(current);
		current = next;
	}
	free(h);
}
