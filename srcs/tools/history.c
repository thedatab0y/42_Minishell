/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:41:59 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:36:17 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

history	*history_init(void)
{
	history *h = (history *)malloc(sizeof(history));
	h->head = NULL;
	h->size = 0;
	return (h);
}

void history_add(history *h, const char *command)
{
	historyEntry *entry = (historyEntry *)malloc(sizeof(historyEntry));
	entry->command = strdup(command);
	entry->next = h->head;
	h->head = entry;
	h->size++;
}

char	*history_get(history *h, int index)
{
	int i;
	
	if (index >= h->size)
		return (NULL);
	historyEntry *current = h->head;
    i = 0;
    while (i < index)
	{
		current = current->next;
		i++;
	}
	return (current->command);
}

void	history_delete(history *h)
{
	historyEntry *current = h->head;
	historyEntry *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->command);
		free(current);
		current = next;
	}
	free(h);
}
