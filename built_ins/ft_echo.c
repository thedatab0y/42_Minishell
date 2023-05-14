/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:42:25 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/07 18:42:27 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// find the len of a string
int	ft_strlen(char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

//compare two strings
int	ft_strncmp(const char *st1, const char *st2, size_t x)
{
	size_t	n;

	n = 0;
	if (x == 0)
		return (0);
	while (n < x - 1 && st1[n] != '\0' && st2[n] != '\0' && st1[n] == st2[n])
	{
		n++;
	}
	return ((unsigned char)st1[n] - (unsigned char)st2[n]);
}

// prtins its arguments to standard output
int	ft_echo(char **args)
{
	bool	newline;

	newline = true;
	if (ft_strncmp(*args, "echo", ft_strlen(*args)) != 0)//if the first argument is not echo, return false
		return (1);
	args++;//if it does, it go on to the next one by incrementing the args ptr
	// "*" dereferences the args pointer to get the value of the argument it points to
	if (*args && ft_strncmp(*args, "-n", ft_strlen("-n") + 1) == 0)
	{
		newline = false;
		args++;
	}
	while (*args)
	{
		if (printf("%s", *args) != ft_strlen(*args))
			return (1);
		if (ft_strlen(*args) != 0 && *(args + 1) != NULL)
			if (printf(" ") != ft_strlen(" "))
				return (1);
		args++;
	}
	if (newline)
		if (printf("\n") != ft_strlen("\n"))
			return (1);
	return (0);
}

// int main()
// {
//     //Basic "echo" command
//     char *args1[] = {"echo", "Hello, world!", NULL};
//     int ret1 = echo(args1);
//     printf("Test 1: Return value = %d\n", ret1);

//     //"echo" command with "-n" option which tell echo not to add a new line
//     char *args2[] = {"echo", "-n", "Hello, world!", NULL};
//     int ret2 = echo(args2);
//     printf("Test 2: Return value = %d\n", ret2);

//     //"echo" command with multiple arguments
//     char *args3[] = {"echo", "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog.", NULL};
//     int ret3 = echo(args3);
//     printf("Test 3: Return value = %d\n", ret3);

// 	//"echo"  nothing
// 	char *args4[] = {"echo", NULL};
//     int ret5 = echo(args4);
//     printf("Test 4: Return value = %d\n", ret1);

//     return 0;
// }