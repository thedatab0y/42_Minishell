#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMANDS 100
#define MAX_ARGS 10

void read_input(char *input) {
    printf("potato> ");
    fgets(input, 1024, stdin);
    input[strcspn(input, "\n")] = '\0';
}

int parse_commands(char *input, char **commands) {
    int num_commands = 0;
    commands[num_commands] = strtok(input, "|");
    while (commands[num_commands] != NULL && num_commands < MAX_COMMANDS) {
        num_commands++;
        commands[num_commands] = strtok(NULL, "|");
    }
    return num_commands;
}

int parse_args(char *command, char **args) {
    int num_args = 0;
    args[num_args] = strtok(command, " ");
    while (args[num_args] != NULL && num_args < MAX_ARGS) {
        num_args++;
        args[num_args] = strtok(NULL, " ");
    }
    return num_args;
}

void execute_command(char **args) {
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) < 0) {
            printf("minishell: command not found: %s\n", args[0]);
            exit(1);
        }
    } else if (pid < 0) {
        printf("minishell: error forking process\n");
    } else {
        waitpid(pid, NULL, 0);
    }
}

int main() {
    char input[1024];
    char *commands[MAX_COMMANDS];
    char *args[MAX_ARGS];
    int num_commands;
    int num_args;
    int i;

    while (1) {
        read_input(input);
        num_commands = parse_commands(input, commands);
        for (i = 0; i < num_commands; i++) {
            num_args = parse_args(commands[i], args);
            execute_command(args);
        }
    }

    return 0;
}
