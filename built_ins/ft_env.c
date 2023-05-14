/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:42:34 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/07 18:42:37 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Define the t_envp struct
typedef struct s_envp {
    char *key;
    char *value;
    struct s_envp *next;
} t_envp;

//-----LIBFT-------//

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		x;

	x = 0;
	if (!s || fd < 0)
		return ;
	while (s[x] != '\0')
	{
		ft_putchar_fd(s[x], fd);
		x++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}



//--------LIBFT---------//

// Find the position of a variable in the envp list
int var_position_in_envp(t_envp *envp_list, char *var_name) {
    int i = 0;
    while (envp_list) {
        if (strcmp(envp_list->key, var_name) == 0) {
            return i;
        }
        envp_list = envp_list->next;
        i++;
    }
    return -1;
}

int	builtin_env(t_envp *envp_list)
{
	if (!envp_list)
		return (1);
	if (var_position_in_envp(envp_list, "PATH") == -1)
	{
		ft_putendl_fd("Myshell: env: No such file or directory", 2);
		return (127);
	}
	while (envp_list)
	{
		ft_putstr_fd(envp_list->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(envp_list->value, 1);
		envp_list = envp_list->next;
	}
	return (0);
}


//testing
int main(int argc, char *argv[]) {
    // Create an example envp list
    t_envp *envp_list = malloc(sizeof(t_envp));
    envp_list->key = "PATH";
    envp_list->value = "/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/Apple/usr/bin:/opt/homebrew/bin:/opt/homebrew/sbin";
    envp_list->next = malloc(sizeof(t_envp));
    envp_list->next->key = "HOME";
    envp_list->next->value = "/Users/bobstone";
    envp_list->next->next = NULL;

    // Test the var_position_in_envp function
    int path_position = var_position_in_envp(envp_list, "PATH");
    printf("PATH is at position %d\n", path_position);
	int path_position1 = var_position_in_envp(envp_list, "HOME");
    printf("HOME is at position %d\n", path_position1);

    // Test the builtin_env function
    printf("Environment variables:\n");
	//int ret =- builtin_env(envp_list);
    builtin_env(envp_list);
   	// printf("Return value: %d\n", ret);

    // Free the memory used by the envp list
    free(envp_list->next);
    free(envp_list);

    return (0);
}


// // Example usage of the t_envp and var_position_in_envp functions
// int main(int argc, char *argv[]) {
//     // Create an example envp list
//     t_envp *envp_list = malloc(sizeof(t_envp));
//     envp_list->key = "PATH";
//     envp_list->value = "/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/Apple/usr/bin:/opt/homebrew/bin:/opt/homebrew/sbin";
//     envp_list->next = malloc(sizeof(t_envp));
//     envp_list->next->key = "HOME";
//     envp_list->next->value = "/Users/bobstone";
//     envp_list->next->next = NULL;
    
//     // Find the position of the "PATH" variable in the envp list
//     int path_position = var_position_in_envp(envp_list, "PATH");
//     printf("PATH is at position %d\n", path_position);
    
//     // Free the memory used by the envp list
//     free(envp_list->next);
//     free(envp_list);
    
//     return 0;
// }

// int main(int argc, char *argv[], char *envp[]) {
//     // Loop through the environment variables and print them
//     for (int i = 0; envp[i] != NULL; i++) {
//         printf("%s\n", envp[i]);
//     }
//     return 0;
// }


