#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// this will free a dynamically allocated str and set its pointer to NULL
// free the memory allocated for each string in the array and then free the 
//memory allocated for the array itself.
void ft_free_str(char **str)
{
    if (str && *str) 
    {
        free(*str);
        *str = NULL; 
    }
}

// find the len of a string
int ft_strlen(char *str)
{
	int x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

// get the current working directory
//need to implement my own ft_printf
// if printf fails, free the string and print an error message
//at last, free the string and set the pointer to null
//at last, setting cwd to NULL to not access freed memory later
int ft_pwd(void)
{
	char *cwd = NULL;

    cwd = getcwd(cwd, 0);
    if (cwd == NULL)
    {
        perror("Error!");
        return (0);
    }
    else if (printf("%s\n", cwd) != ft_strlen(cwd) + 1)
    {
        ft_free_str(&cwd);
        perror("\nError: error occured with printf!");
        return (0);
    }
    ft_free_str(&cwd);
    cwd = NULL;

    return (1);
}

// int main()
// {
// 	//char *cwd;
//     ft_pwd();
// 	return (0);
// }
