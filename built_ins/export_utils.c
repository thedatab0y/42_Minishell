/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:03:20 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/10 11:51:29 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_meta_builtin(char c)
{
	if (c == '!' || c == '@' || c == '$' || c == '^' || c == '%' || c == ':' \
	|| c == '*' || c == '[' || c == ']' || c == '/' || c == '{' || c == '}' \
	|| c == ',' || c == '.' || c == '?' || c == '+' || c == '~' || c == '-' \
	|| c == '=' || c == '\\' || c == '#' || c == '&' || c == '*' || c == '\'' \
	|| c == '\"' || c == '`' || c == '(' || c == ')' || c == '|' || c == ';' \
	|| c == '<' || c == '>')
		return (1);
	return (0);
}

void	free_strings(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

void	export_identifier_error(char *command)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}