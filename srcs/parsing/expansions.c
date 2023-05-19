/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:37:26 by busmanov          #+#    #+#             */
/*   Updated: 2023/05/18 10:37:50 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	squish_token(t_mini *mini, t_token *token, t_token *prev)
{
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	if (prev)
	{
		token->prev = prev;
		token->next = prev->next;
		prev->next->prev = token;
		prev->next = prev->next;
	}
	else
	{
		token->prev = token;
		token->next = mini->start;
		token->next->prev = token;
		mini->start = mini->start;
	}
	if (mini->start->prev)
		mini->start = mini->start->prev;
	else
		mini->start = mini->start;
}

//this function performs a character copy operation
static int	cpy_var(char *dest, const char *src, int position)
{
	int		x;

	x = 0;
	while (src[x])
		dest[position++] = src[x++];
	return (x);
}

static	void	insert_var(t_expansions *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;
	int		cpy_var_result;

	env_value = get_var_value(arg, ex->j, env, ret);
	if (env_value)
	{
		cpy_var_result = cpy_var(ex->new_arg, env_value, ex->i);
		ex->i += cpy_var_result;
	}
	ft_memdel(env_value);
	if (arg[ex->j] == '?')
		ex->j++;
	else if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	else if (arg[ex->j - 1] != '?')
		ex->j++;
}

char	*expansions(char *arg, t_env *env, int ret)
{
	t_expansions	ex;
	int				new_arg_len;

	new_arg_len = arg_alloc_len(arg, env, ret);
	ex.new_arg = malloc(sizeof(char) * new_arg_len + 1);
	if (ex.new_arg == NULL)
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.new_arg[ex.i++] = '$';
			else
				insert_var(&ex, arg, env, ret);
		}
		ex.new_arg[ex.i++] = arg[ex.j++];
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}
