/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:43:00 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/07 18:43:02 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//ft_split
static int	ft_count_words(const char *str, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (str[x])
	{
		if (str[x] == c)
			x++;
		else
		{
			y++;
			while (str[x] != '\0' && str[x] != c)
				x++;
		}
	}
	return (y);
}

static char	*ft_write_words(const char *str, char c)
{
	int		counterr;
	char	*ptr;

	counterr = 0;
	while (*str && *str == c)
		str++;
	while (str[counterr] && str[counterr] != c)
		counterr++;
	ptr = (char *)malloc(sizeof(char) * (counterr + 1));
	if (ptr == NULL)
		return (NULL);
	counterr = 0;
	while (str[counterr] && str[counterr] != c)
	{
		ptr[counterr] = str[counterr];
		counterr++;
	}
	ptr[counterr] = '\0';
	return (ptr);
}

static void	ft_free_words(int i, char **pptr)
{
	while (i > 0)
	{
		free(pptr[i - 1]);
		i--;
	}
	free(pptr);
}

static int	ft_free(int counter, char **pptr)
{
	if (pptr[counter] == NULL)
	{
		ft_free_words(counter, pptr);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**pptr;
	int		counter;
	int		num_word;

	if (!s)
		return (NULL);
	num_word = ft_count_words(s, c);
	pptr = (char **)malloc(sizeof(char *) * (num_word + 1));
	if (pptr == NULL)
		return (NULL);
	counter = 0;
	while (counter < num_word)
	{
		while (*s && *s == c)
			s++;
		pptr[counter] = ft_write_words(s, c);
		if (!(ft_free(counter, pptr)))
			return (NULL);
		while (*s && *s != c)
			s++;
		counter++;
	}
	pptr[counter] = NULL;
	return (pptr);
}
//--------

//strerror function to obtain the error message corresponding to the error code
//stop the program 
void stop(const char *shell_name)
{
    int errnum = errno;
    const char *error_msg = strerror(errnum);

    if (errnum != 0 && errnum != 1)
    {
        printf("%s: %s\n", shell_name, error_msg);
        exit(1);
    }
    else if (errnum == 0)
    {
        exit(0);
    }
    else
    {
        exit(1);
    }
}

// int main()
// {
//     const char *shell_name = "my_shell";

//     // Test with no error
//     stop(shell_name);

//     // Test with error code 2 (ENOENT)
//     if (access("non_existent_file", F_OK) == -1)
//     {
//         stop(shell_name);
//     }

//     // Test with error code 13 (EACCES)
//     if (access("/etc/shadow", R_OK) == -1)
//     {
//         stop(shell_name);
//     }

//     return 0;
// }



int ft_strncmp(const char *str1, const char *str2)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i += 1;
	}
	return (s1[i] - s2[i]);
}

//compare environment variables with the command-line arguments
int	ft_unset(char *arg, char *env, char *shell_name)
{
	int		i;
	int		diff;
	char	**words_env;

	words_env = ft_split(env, '=');
	if (!words_env)
		stop(shell_name);
	diff = ft_strncmp(arg, words_env[0]);
	i = -1;
	while (words_env[++i])
		free (words_env[i]);
	free(words_env);
	return (diff);
}

// int main(void)
// {
//     char *arg = "HOME";
//     char *env = "HOME=/home/user";
//     char *shell_name = "my_shell";
//     int result = ft_unset(arg, env, shell_name);
//     printf("Comparison result: %d\n", result);
//     return 0;
// }
