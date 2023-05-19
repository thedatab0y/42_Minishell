/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:21:20 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/18 16:15:20 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	ft_export_checker(char **args, t_env *env, t_env *secret)
{
	int		new_env;
	int		error_ret;

	new_env = 0;
	error_ret = is_valid_env(args[1]);
	if (args[1][0] == '=')
		error_ret = -3;
	if (error_ret <= 0)
		return (print_error(error_ret, args[1]));
	if (error_ret == 2)
		new_env = 1;
	else
		new_env = is_in_env(env, args[1]);
	if (new_env == 0)
	{
		if (error_ret == 1)
			env_add(args[1], env);
		env_add(args[1], secret);
	}
	return (SUCCESS);
}

//print error for cd
char	*oldpwd_checker(t_env *env, size_t len)
{
	char	*oldpwd;
	int		s_alloc;

	s_alloc = ft_strlen(env->value) - len;
	oldpwd = malloc(sizeof(char) * s_alloc + 1);
	if (!oldpwd)
		return (NULL);
	return (oldpwd);
}

void	print_error_cd(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}
