/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:41:59 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:13:54 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

History	*history_init(void)
{
	History *h = (History *)malloc(sizeof(History));
	h->head = NULL;
	h->size = 0;
	return (h);
}

void history_add(History *h, const char *command)
{
	HistoryEntry *entry = (HistoryEntry *)malloc(sizeof(HistoryEntry));
	entry->command = strdup(command);
	entry->next = h->head;
	h->head = entry;
	h->size++;
}

char	*history_get(History *h, int index)
{
	int i;
	
	if (index >= h->size)
		return (NULL);
	HistoryEntry *current = h->head;
    i = 0;
    while (i < index)
	{
		current = current->next;
		i++;
	}
	return (current->command);
}

void	history_delete(History *h)
{
	HistoryEntry *current = h->head;
	HistoryEntry *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->command);
		free(current);
		current = next;
	}
	free(h);
}
