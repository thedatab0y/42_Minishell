/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:21:23 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/07 18:41:29 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>//library for chdir() function
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>//library for waitpid() function to wait for a child process to terminate
# include <sys/types.h> //library for various data types such as pid_t
# include <fcntl.h> //library for file control options such as O_RDONLY, O_WRONLY
#include <string.h>

int ft_strlen(char *string)
{
	int x;

	x = 0;
	while (string[x])
		x++;
	return(x);
}

char *ft_strpbrk(const char *str, const char *charset) 
{
	const char *p;
	while (*str != '\0')
	{ // Loop through the input string
		p = charset;
	while (*p != '\0')
	{ // Loop through the charset
      if (*str == *p)
        return (char *)str; // Return pointer to the first matching character
      p++;
    }
    str++;
  }
  return NULL; // Return NULL if no matching character is found
}

// function locates the first occurrence in the string s of any of the bytes in the string accept.
char *ft_strtok(char *str, const char *delim) {
  static char *last = NULL; // Static variable to keep track of the last string
  if (str != NULL) {
    last = str; // If the input string is not NULL, update last to point to it
  }
  if (last == NULL) {
    return NULL; // If last is NULL, there's nothing to tokenize, so return NULL
  }
  char *start = last; // Pointer to the start of the next token
  char *end = strpbrk(start, delim); // Pointer to the end of the next token
  if (end != NULL) {
    *end = '\0'; // Replace the delimiter with null terminator
    last = end + 1; // Update last to point to the start of the next token
  } else {
    last = NULL; // If no more delimiters found, reset last to NULL
  }
  return start; // Return pointer to the start of the current token
}

//function that outputs an error message when cd fails
int cd_error(char *arg)
{
	write(1, "bash: cd: ", ft_strlen("bash: cd: "));///Print "bash: cd: "
	perror(arg);//Print the error message specified by the argument
	return (1);//Return 1 to indicate failure
}

// function that compares two strings for a given length.
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

//function that concatenates two strings.
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[x] != '\0')
	{
		str[x] = s1[x];
		x++;
	}
	while (s2[y] != '\0')
	{
		str[y + x] = s2[y];
		y++;
	}
	str[x + y] = '\0';
	return (str);
}

void	*ft_memcpy(void *to, const void *from, size_t n)
{
	unsigned char	*pto;
	unsigned char	*pfrom;
	size_t			x;

	if (to == NULL && from == NULL)
		return (NULL);
	pto = (unsigned char *)to;
	pfrom = (unsigned char *)from;
	x = 0;
	while (x < n)
	{
		pto[x] = pfrom[x];
		x++;
	}
	return (pto);
}

void		*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	ft_memcpy(new_ptr, ptr, size);
	return (new_ptr);
}


//ft_putenv below

// Initializes the environment variables array
char** init_envp(int* env_size) 
{
    *env_size = 8; // set the initial size
    char **envp = (char **)malloc(*env_size * sizeof(char *));
    return envp;
}

// Searches for an existing environment variable with the same name
int find_env_var(char** envp, int env_count, char* str)
{
    int i = 0;
    size_t len;

	len = ft_strlen(str);
    while (i < env_count) {
        if (ft_strncmp(envp[i], str, len) == 0 && envp[i][len] == '=') {
            return i;
        }
        i++;
    }
    return -1; //returns the index of the environment variable in the
	// array if it is found, or -1 if it is not found.
}

// Doubles the size of the environment variables array if necessary
char** double_envp_size(char** envp, int* env_size)
{
    *env_size *= 2;
    char **new_envp;

	new_envp = (char **)ft_realloc(envp, *env_size * sizeof(char *));
    return new_envp;
}

// Adds a new environment variable to the array
int add_env_var(char** envp, int* env_count, int* env_size, char* str) 
{
	char *new_str;

    if (*env_count >= *env_size) {
        envp = double_envp_size(envp, env_size);
        if (envp == NULL) {
            return -1;
        }
    }
	new_str = strdup(str);
    if (new_str == NULL) {
        return -1;
    }
    envp[*env_count] = new_str;
    (*env_count)++;
    return 0;
}

// Replaces the value of an existing environment variable with the same name
int replace_env_var(char** envp, int index, char* str) {
    char *new_str;

	new_str = strdup(str);
    if (new_str == NULL) {
        return -1;
    }
    free(envp[index]);
    envp[index] = new_str;
    return 0;
}


// Adds or replaces an environment variable in the array
int ft_putenv(char *str) {
    static char **envp = NULL;
    static int env_size = 0;
    static int env_count = 0;
	int index;

    if (envp == NULL)  // If this is the first time this function is 
	//called, initialize envp with the current process's environment variables.
	{
        envp = init_envp(&env_size);// allocate memory for envp and copy the current env vars
        if (envp == NULL) {
            return -1;
        }
    }
	// Search for the environment variable in envp
    index = find_env_var(envp, env_count, str);
    if (index >= 0) {// returns the index of the variable or -1 if not found
        return replace_env_var(envp, index, str); // variable already exists,update its value.
    }
	// The variable doesn't exist, so add it to envp.
    return add_env_var(envp, &env_count, &env_size, str);// returns 0 on success, -1 on failure
}
//done ft_putenv



//function that sets the value of the PWD environment variable to the current working directory.
void set_pwd(void)
{
	char	*cwd;
	char	*toadd;

	cwd = getcwd(NULL, 4096); //get current working directory
	toadd = ft_strjoin("PWD=", cwd); //create a string "PWD=current_working_directory"
	free(cwd);
	ft_putenv(toadd); // write ft_putenv . set the environment variable PWD to the current working directory
	free(toadd);
}

//function that executes the "cd" command.
int cd (char **args, int args_count)
{
	char	*home;

	if (args_count == 0) //if no arguments provided with cd command
	{
		home = getenv("HOME");  //get the value of the environment variable HOME
		if (!home || !(*home)) //if HOME environment variable is not set
		{
			write(1, "bash: cd: HOME not set\n", ft_strlen("bash: cd: HOME not set\n"));
			return (1);
		}
		if(chdir(home) == -1) //change directory to HOME directory
			return (cd_error(home));
	}
	else if (args_count == 1) //if one argument provided with cd command
	{ 
		if (chdir(args[0]) == -1) //change directory to the argument provided
			return (cd_error(args[0]));
	}
	else //if more than one argument provided with cd command
	{
		write(1, "cd: too many arguments\n", ft_strlen("cd: too many arguments\n"));
		return (1);
	}
	set_pwd(); //set the PWD environment variable to the current working directory
	return (0);
}

// int main(void) {
//     char *args[] = {"/usr/local/bin"}; //change directory to /usr/local/bin
//     int args_count = sizeof(args) / sizeof(args[0]);
//     int cd_return_value = cd(args, args_count);

//     if (cd_return_value == 0) {
//         printf("Directory changed successfully\n");
//     } else {
//         printf("Directory change failed\n");
//     }

//     return 0;
// }



// int main(int argc, char **argv)
// {
//     char *dir1 = "/usr/bin";
//     char *dir2 = "/usr/local/bin";
//     char *dir3 = "/opt/local/bin";
//     char *dir4 = "/usr/sbin";
//     char *dir5 = "/sbin";
//     char *args[3];
//     int args_count;

//     printf("Testing cd with no arguments:\n");
//     args_count = 0;
//     cd(args, args_count);
//     printf("\n");

//     printf("Testing cd with one argument:\n");
//     args[0] = dir1;
//     args_count = 1;
//     cd(args, args_count);
//     printf("\n");

//     printf("Testing cd with invalid directory:\n");
//     args[0] = "nonexistent_directory";
//     args_count = 1;
//     cd(args, args_count);
//     printf("\n");

//     printf("Testing cd with too many arguments:\n");
//     args[0] = dir2;
//     args[1] = dir3;
//     args[2] = dir4;
//     args_count = 3;
//     cd(args, args_count);
//     printf("\n");

//     printf("Testing cd with HOME environment variable not set:\n");
//     unsetenv("HOME");
//     args_count = 0;
//     cd(args, args_count);
//     printf("\n");

//     printf("Testing cd with HOME environment variable set to a valid directory:\n");
//     setenv("HOME", dir5, 1);
//     args_count = 0;
//     cd(args, args_count);
//     printf("\n");

//     return 0;
// }