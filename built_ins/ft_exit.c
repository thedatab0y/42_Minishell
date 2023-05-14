/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busmanov <busmanov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:42:48 by busmanov          #+#    #+#             */
/*   Updated: 2023/04/07 18:42:50 by busmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//depending on which platform the program is running on, it sets an appropriate exit status using the control->exit_status variable.
//If the platform is macOS, the exit status is set to 255, but for Linux, the exit status is set to 2.
//This is necessary because the exit status is used by other programs or scripts that may call this program, so they need to know whether the program executed successfully or not.
//The code 
			//  control->exit_status = (IS_APPLE ? 255 : 2);
				//sets the exit status of the program based on whether it is being executed on an Apple platform or not.
//The ? operator used here is called a ternary operator, which is like a shorthand for an if...else statement.



#include <unistd.h>
#include <stdlib.h> // for exit()
#include <stdio.h> // for printf

#define IS_APPLE 0 // macro defined for differentiating between Linux and Apple

typedef struct s_control // struct to store some info about the shell
{
    int quit; // indicates if the shell should keep running or not
    pid_t parent_pid; // process id of the main shell process.
						// used to determine if the command is being executed by the main shell
    unsigned char exit_status; // stores exit status in form of 8-bit unsigned int
} t_control;

size_t ft_array_len(char **arr)
{
    size_t len; // if arr is NULL, return 0

    len = 0;
    if (arr == NULL)
        return (len);
    while (arr[len])
        len++;
    return (len); // return the length of the array
}

// if c is a digit character from 0 to 9 return 1 else 0
int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int ft_isonly_ft(char *str, int (*f)(int), int start)
{
    if (!str || !f)
        return (0);

    while (str[start]) // iterate over index after start till reaching '\0'
    {
        if (!f((int)str[start])) // if f of str is false, like (!ft_isdigit('e')) then return 0 early
            return (0);
        start++;
    }

    return (1); // if all elems were digits and successfully evaluated, return 1
}

// return integer formed
int ft_atoi(const char *str)
{
    int sign = 1;
    int res = 0;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
           || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (sign * res);
}

// print error message in specified format
void ft_perror(char *cmd, char *arg, char *msg)
{
    printf("ERROR: %s: %s%s\n", cmd, msg, (arg ? arg : ""));
}

int exit_builtin(char **argv, t_control *control)
{
    int has_sign;

    control->quit = 1; // switch quit flag on
    if (control->parent_pid == getpid()) // check if this command is being executed by the main shell
        printf("exit\n"); // if yes, print "exit" to STDOUT(screen)
     if (!argv || !argv[1])
        return (1); // return 1 for successful execution
					// here, I am asssuming that the first argument is always "exit"
    has_sign = (argv[1][0] == '-' || argv[1][0] == '+'); // check if first elem of the second argument has sign - or +
    if (!ft_isonly_ft(argv[1] + has_sign, ft_isdigit, 1)) // check if the second arg contains only digits
    {
        ft_perror("exit", argv[1], "numeric argument required"); // if not, print numeric argument required error msg
		// if IS_APPLE is true, then the below evaluates to 255(else to 2) and assign to control->exit_status
        control->exit_status = (IS_APPLE ? 255 : 2); //set appropriate exit status based on which platform I am on
    }
    else if (ft_array_len(argv) >= 3)
    {
        ft_perror("exit", NULL, "too many arguments"); // if there are more than two arguments provided, print too many args error msg
        control->quit = 0; // unset quit flag
        control->exit_status = 1; //set the exit status according to the error
    }
    else
        control->exit_status = (unsigned char)ft_atoi(argv[1]); // this sets the exit status for the shell
		// control variable stores the informatin about the shell and one of its fields
		// (exit status) gets updated to the integer value of the second arg passed to the "exit" command by calling ft_atoi()
		//argv[1] refers to the second arg of the args[] array in main() function 
    printf("exit\n"); // displays the word "exit"
    exit(0); // immediately terminates the program
}


// int main(void)
// {
//     t_control control = {0}; // initializes a t_control struct named control.
// 							// {0} syntax sets all of its fields to zero to avoid garbage values
// 							// also to make sure all fields start at the same point
//     char *args[] = {"exit", "127", NULL}; // special purpose args[] array which will only be used for executing "exit" command with
// 										// an additional parameter 0. 

//     exit_builtin(args, &control); // this invokes exit_builtin() function to execute the "exit" command.

//     return (0);
// }
