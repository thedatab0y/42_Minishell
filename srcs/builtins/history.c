/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:27:30 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 18:36:38 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_history(t_mini *mini)
{
	int	i;

	if (mini->history->size == 0)
	{
		printf("No commands in history.\n");
		return (SUCCESS);
	}
	i = 0;
	while (i < mini->history->size)
	{
		printf("%d: %s\n", i + 1, history_get(mini->history, i));
		i++;
	}
	return (SUCCESS);
}
