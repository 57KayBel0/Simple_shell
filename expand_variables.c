#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

// Function to expand variables in the command
void expand_variables(char* command) {
    char expanded_command[MAX_COMMAND_LENGTH] = "";
    char variable[3] = ""; // To store "$?", "$$"
    int var_index = 0;
    int i = 0;

    while (command[i] != '\0') {
        if (command[i] == '$') {
            i++; // Move to the character after '$'

            // Check for special variables
            if (command[i] == '?') {
                snprintf(variable, sizeof(variable), "%d", WEXITSTATUS(errno));
                i++; // Move to the character after '?'
            } else if (command[i] == '$') {
                snprintf(variable, sizeof(variable), "%d", getpid());
                i++; // Move to the character after '$'
            } else {
                // Unsupported variable, treat '$' as a regular character
                variable[0] = '$';
            }

            // Append the expanded variable to the new command
            strcat(expanded_command, variable);
            var_index = strlen(expanded_command);
        } else {
            expanded_command[var_index++] = command[i++];
        }
    }

    expanded_command[var_index] = '\0';

    // Copy the expanded command back to the original command
    strcpy(command, expanded_command);
}

// Function to execute a single command
void execute_command(char* command) {
    char* arguments[MAX_ARGUMENTS];
    char* token;
    int i = 0;

    // Split the command into arguments
    token = strtok(command, " ");
    while (token != NULL) {
        arguments[i++] = token;
        token = strtok(NULL, " ");
    }
    arguments[i] = NULL;

    // Fork a new process to execute the command
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        // Child process
        execvp(arguments[0], arguments);
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char input[MAX_COMMAND_LENGTH];

    while (true) {
        printf("Shell> ");
        fgets(input, MAX_COMMAND_LENGTH, stdin);

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Expand variables in the command
        expand_variables(input);

        // Execute the command
        execute_command(input);
    }

    return 0;
}

