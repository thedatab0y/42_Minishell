/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:34:07 by busmanov          #+#    #+#             */
/*   Updated: 2023/05/19 16:13:42 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_type(prev, INPUT))
		input(mini, token);
	else if (is_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->no_exec == 0)
		exec_cmd(mini, token);
}

void	process_tokens(t_mini *mini, t_token *token)
{
	int	status;

	mini->charge = 1;
	mini->parent = 1;
	mini->last = 1;
	redir_and_exec(mini, token);
	reset_std(mini);
	close_fds(mini);
	reset_fds(mini);
	waitpid(-1, &status, 0);
	status = WEXITSTATUS(status);
	if (mini->last == 0)
	{
		mini->ret = status;
	}
	if (mini->parent == 0)
	{
		free_token(mini->start);
		exit(mini->ret);
	}
	mini->no_exec = 0;
}

void	minishell(t_mini *mini)
{
	t_token	*token;

	token = next_run(mini->start, NOSKIP);
	if (is_types(mini->start, "TAI"))
	{
		token = mini->start->next;
	}
	while (mini->exit == 0 && token)
	{
		process_tokens(mini, token);
		token = next_run(token, SKIP);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.exit = 0;
	mini.ret = 0;
	mini.no_exec = 0;
	mini.history = history_init();
	reset_fds(&mini);
	env_init(&mini, env);
	secret_env_init(&mini, env);
	increment_shell_level(mini.env);
	while (mini.exit == 0)
	{
		sig_init();
		parse(&mini);
		if (mini.start != NULL && check_line(&mini, mini.start))
			minishell(&mini);
		free_token(mini.start);
	}
	free_env(mini.env);
	free_env(mini.secret_env);
	history_delete(mini.history);
	return (mini.ret);
}
